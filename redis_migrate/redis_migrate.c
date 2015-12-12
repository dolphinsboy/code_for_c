#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <glib.h>
#include <errno.h>
#include <hiredis.h>
#include "redis_migrate.h"

char *from_host = "127.0.0.1";
guint from_port = 15379;
char *to_host = "127.0.0.1";
guint to_port = 8379;

char *keys_file = "./keys.file";
guint threads_num = 4;
gboolean program_version = FALSE;

redisContext *redis_context = NULL;
redisReply *redis_reply = NULL;

gchar *logfile = NULL;
FILE *logoutfile = NULL;
guint verbose = 3;

void no_log(const gchar*log_domain, GLogLevelFlags log_level, const gchar *message, gpointer user_data);
void write_log_file(const gchar*log_domain, GLogLevelFlags log_level, const gchar *message, gpointer user_data);
void create_redis_connection();
void *process_queue(struct thread_data *td); 
void set_verbose(guint verbosity);
gboolean read_keys(FILE *keyfile, struct configuration* conf);
void migrate_one_key(char *keyname);
void add_job(struct configuration* conf, char *keyname);


GOptionEntry common_entries[] = {
   {"fromhost", 'F', 0, G_OPTION_ARG_STRING, &from_host, "Redis cluster host", NULL},
   {"fromport", 'P', 0, G_OPTION_ARG_INT, &from_port, "Redis cluster port", NULL},
   {"tohost", 'T', 0, G_OPTION_ARG_STRING, &to_host, "Redis master host", NULL},
   {"toport", 'O', 0, G_OPTION_ARG_INT, &to_port, "Redis master port", NULL},
   {"keys_file", 'K', 0, G_OPTION_ARG_STRING, &keys_file, "Migrate keys file", NULL},
   {"threads_num", 'N',0, G_OPTION_ARG_INT, &threads_num, "Numbers of threads to use,default 4", NULL},
   {"logfile", 'L', 0, G_OPTION_ARG_FILENAME, &logfile, "Log file name to user, by default stdout is used", NULL},
   {"Version", 'V', 0, G_OPTION_ARG_NONE, &program_version, "Show program version and exit", NULL},
   {"verbose", 'v', 0, G_OPTION_ARG_INT, &verbose, 
       "Verbosity of output, 0 = slient, 1 = errors, 2 = warnings, 3 = info, default 2", NULL},

   {NULL, 0, 0, G_OPTION_ARG_NONE, NULL, NULL, NULL}
};

void no_log(const gchar*log_domain, GLogLevelFlags log_level, const gchar *message, gpointer user_data)
{
    (void) log_domain;
    (void) log_level;
    (void) message;
    (void) user_data; 
}

void set_log_file(guint verbosity){
    GLogLevelFlags log_level;

    if(logfile){
        logoutfile = g_fopen(logfile, "w");

        if(!logoutfile){
            g_critical("can't open file %s, errno=%d", logfile, errno);
            exit(EXIT_FAILURE);
        }
    }

    switch(verbosity){
        case 0:
            g_log_set_handler(NULL,(GLogLevelFlags)G_LOG_LEVEL_MASK, no_log, NULL);
            break;
        case 1:
            log_level = G_LOG_LEVEL_WARNING | G_LOG_LEVEL_MESSAGE;
            g_log_set_handler(NULL,log_level, no_log, NULL);

            if(logfile){
                log_level = G_LOG_LEVEL_ERROR | G_LOG_LEVEL_ERROR;
                g_log_set_handler(NULL, log_level, write_log_file, NULL);
            }
            break;
        case 2:
            log_level = G_LOG_LEVEL_MESSAGE;
            g_log_set_handler(NULL,log_level, no_log, NULL);

            if(logfile){
                log_level = G_LOG_LEVEL_WARNING | G_LOG_LEVEL_ERROR | G_LOG_LEVEL_WARNING;
                log_level = log_level | G_LOG_LEVEL_CRITICAL|G_LOG_LEVEL_MESSAGE;

                g_log_set_handler(NULL, log_level, write_log_file, NULL); 
            }

            break;
        default:
            if (logfile)
                g_log_set_handler(NULL, (GLogLevelFlags)(G_LOG_LEVEL_MASK), write_log_file, NULL);
            break;
    }
}

void create_redis_connection(){
    struct timeval timeout = {1, 50};
    redis_context = redisConnectWithTimeout(from_host, from_port, timeout);
    if (redis_context == NULL || redis_context->err){
        if (redis_context){
             printf("Connection error:%s\n", redis_context->errstr);
             redisFree(redis_context);
         }else{
             printf("Connection error: can't allocate redis context\n");
	 }
         exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]){
    GError *error = NULL;
    GOptionContext *context;

    FILE *mdfile = NULL;
    struct configuration conf= { NULL, NULL, NULL, 0 };

    context = g_option_context_new("redis migrate data from cluster to master by MIGRATE cmd");
    GOptionGroup *main_group = g_option_group_new("main",
                                    "Main options",
				    "Main options",
				    NULL, NULL);

    g_option_group_add_entries(main_group, common_entries);
    g_option_context_set_main_group(context, main_group);

   if (!g_option_context_parse(context, &argc, &argv, &error)){
        g_print("option parsing failed:%s, try --help\n", error->message);
        exit(EXIT_FAILURE);
    }

   set_log_file(verbose);

    g_print("from_host=%s\n", from_host);

    mdfile = fopen(keys_file, "r");

    if(!mdfile){
        g_critical("Couldn't read keyname from keys_file (%d)", errno);
        exit(EXIT_FAILURE);
    }
    //create_redis_connection();

    conf.queue = g_async_queue_new();
    conf.ready = g_async_queue_new();

    read_keys(mdfile, &conf);

    guint n;
    GThread **threads = g_new(GThread*, threads_num);
    struct thread_data* td = g_new(struct thread_data, threads_num);

    for (n = 0; n < threads_num; n++){
        td[n].thread_id = n + 1;
        td[n].conf = &conf;
        threads[n] = g_thread_new(NULL, (GThreadFunc)process_queue, &td[n]);

        g_async_queue_pop(conf.ready);
    }

    g_async_queue_unref(conf.ready);
    g_message("%d threads created", threads_num);

    for (n = 0; n < threads_num; n++){
        struct job * jb = g_new0(struct job, 1);
        jb->type = JOB_SHUTDOWN;
        g_async_queue_push(conf.queue, jb);
    }

    for (n = 0; n <threads_num; n++)
        g_thread_join(threads[n]);

    g_async_queue_unref(conf.queue);
    g_free(td);
    g_free(threads);

    fclose(mdfile);

    return 0;
}

void migrate_one_key(char *keyname)
{
    char cmd[128];
    sprintf(cmd, "MIGRATE %s %d %s 0 1000 COPY", to_host, to_port, keyname);
    redis_reply = redisCommand(redis_context, cmd);
    g_message("Migrate Result:%s", redis_reply->str);

}

void *process_queue(struct thread_data *td)
{
    struct configuration *conf = td->conf;
    g_async_queue_push(conf->ready,GINT_TO_POINTER(1));

    struct job* jb = NULL;
    struct migrate_job* mjb = NULL;

    for(;;){
        jb = (struct job*)g_async_queue_pop(conf->queue);

        switch(jb->type){
            case JOB_MIGRATE:
                mjb = (struct migrate_job *)jb->data;
                g_message("JOB_MIGRATE keyname=%s in thread %d", mjb->keyname, td->thread_id);
                //migrate_one_key(mjb->keyname);
                g_free(jb);
                break;
			case JOB_TEST:
                mjb = (struct migrate_job *)jb->data;
                g_message("JOB_TEST in thread %d, keyname=%s" , td->thread_id, mjb->keyname);
				g_free(jb);
                break;

            case JOB_SHUTDOWN:
                g_message("Thread %d shutting down", td->thread_id);
                g_free(jb);
                return NULL;
                break;

        }
    }
}

gboolean read_keys(FILE* file, struct configuration *conf)
{
    char *keyname = malloc(60);
    size_t len = 0;
    ssize_t n_read;

    while((n_read = getline(&keyname, &len, file)) != -1){
        keyname[n_read-1] = '\0';
        add_job(conf, keyname);
        keyname = malloc(60);
    }
}

void add_job(struct configuration* conf, char *keyname)
{
    struct job *j = g_new0(struct job, 1); 
    struct migrate_job *mj = g_new0(struct migrate_job, 1); 
    j->data = (void*) mj; 

    j->type = JOB_MIGRATE;

    mj->keyname = keyname;
    g_async_queue_push(conf->queue, j); 

}

void write_log_file(const gchar *log_domain, GLogLevelFlags log_level, const gchar *message, gpointer user_data) {
    (void) log_domain;
    (void) user_data;

    gchar date[20];
    time_t rawtime;
    struct tm timeinfo;

    time(&rawtime);
    localtime_r(&rawtime, &timeinfo);
    strftime(date, 20, "%Y-%m-%d %H:%M:%S", &timeinfo);

    GString* message_out = g_string_new(date);
    if (log_level & G_LOG_LEVEL_DEBUG) {
        g_string_append(message_out, " [DEBUG] - ");
    } else if ((log_level & G_LOG_LEVEL_INFO)
        || (log_level & G_LOG_LEVEL_MESSAGE)) {
        g_string_append(message_out, " [INFO] - ");
    } else if (log_level & G_LOG_LEVEL_WARNING) {
        g_string_append(message_out, " [WARNING] - ");
    } else if ((log_level & G_LOG_LEVEL_ERROR)
        || (log_level & G_LOG_LEVEL_CRITICAL)) {
        g_string_append(message_out, " [ERROR] - ");
    }    

    g_string_append_printf(message_out, "%s\n", message);
    if (write(fileno(logoutfile), message_out->str, message_out->len) <= 0) { 
        fprintf(stderr, "Cannot write to log file with error %d.  Exiting...", errno);
    }    
    g_string_free(message_out, TRUE);
}  
