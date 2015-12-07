#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <glib.h>

guint verbosity = 2;
gchar *logfile= "./tmp.log";
FILE *logoutfile= NULL;


void write_log_file(const gchar *log_domain,
        GLogLevelFlags log_level, 
        const gchar *message, 
        gpointer user_data);

void no_log(const gchar *log_domain, 
        GLogLevelFlags log_level, 
        const gchar *message, 
        gpointer user_data)
{
    (void) log_domain;
    (void) log_level;
    (void) message;
    (void) user_data;

}

void write_log_file(const gchar *log_domain, 
        GLogLevelFlags log_level, 
        const gchar *message, 
        gpointer user_data)
{
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
void set_verbose(guint verbosity)
{
    if(logfile){
        logoutfile = g_fopen(logfile, "w");

        if(!logoutfile){
            g_critical("can't open file %s, errno=%d", logfile, errno);
            exit(EXIT_FAILURE);
        }
    }

    switch (verbosity){
        case 0:
            g_log_set_handler(NULL,(GLogLevelFlags)G_LOG_LEVEL_MASK, no_log, NULL);
            break;
        case 1:
            g_log_set_handler(NULL,
                (GLogLevelFlags)(G_LOG_LEVEL_WARNING | G_LOG_LEVEL_MESSAGE),
                no_log, NULL);

            if (logfile){
                g_log_set_handler(NULL,
                    (GLogLevelFlags)(G_LOG_LEVEL_ERROR | G_LOG_LEVEL_ERROR),
                    write_log_file, NULL);
            }
            break;
        case 2:
            g_log_set_handler(NULL, (GLogLevelFlags)(G_LOG_LEVEL_MESSAGE), no_log, NULL);

            if (logfile){
                g_log_set_handler(NULL, (GLogLevelFlags)(G_LOG_LEVEL_WARNING | G_LOG_LEVEL_ERROR | G_LOG_LEVEL_WARNING |                    G_LOG_LEVEL_ERROR | G_LOG_LEVEL_CRITICAL|G_LOG_LEVEL_MESSAGE), write_log_file, NULL);
            }
            break;
        default:
            if (logfile)
                g_log_set_handler(NULL, (GLogLevelFlags)(G_LOG_LEVEL_MASK), write_log_file, NULL);
            break;
    }
}



int main(int argc, char *argv[])
{
    set_verbose(verbosity);

    g_message("Test %s", ",Hello log");
    g_critical("Crital %s", "Hello");

    return 0;
}
