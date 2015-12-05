#include <glib.h>

enum job_type{ JOB_TEST1, JOB_TEST2, JOB_SHUTDOWN};

struct configuration{
    GAsyncQueue* queue;
    GAsyncQueue* ready;
    GMutex *mutex;

    int done;
};

struct job{
    enum job_type type;
    void *data;
    struct configuration * conf;
};

struct migrate_job{
    char *keyname;
    char *host;
    char *port;
};

struct thread_data{
    guint thread_id;
    struct configuration *conf;
};

void *process_queue(struct thread_data* td)
{
    struct configuration *conf = td->conf;

    g_async_queue_push(conf->ready,GINT_TO_POINTER(1));

    struct job* jb = NULL;
    struct migrate_job* mjb = NULL;


    for(;;){
        jb = (struct job*)g_async_queue_pop(conf->queue);

        switch(jb->type){
            case JOB_TEST1:
                g_message("JOB_TEST1 in thread %d" , td->thread_id);

                g_free(jb);
                break;
            case JOB_TEST2:
                g_message("JOB_TEST2 in thread %d", td->thread_id);
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

void add_job(struct configuration* conf)
{
    struct job *j = g_new0(struct job, 1);
    struct migrate_job *mj = g_new0(struct migrate_job, 1);
    j->data = (void*) mj;

    j->type = JOB_TEST2;

    mj->keyname = "test";
    mj->host = "localhost";
    mj->port = 3303;

    g_async_queue_push(conf->queue, j);

}

int main(int argc, char *argv[])
{
    guint n_threads = 3;
    guint n;

    struct configuration conf= { NULL, NULL, NULL, 0 };

    GThread **threads = g_new(GThread*, n_threads);
    struct thread_data* td = g_new(struct thread_data, n_threads);

    conf.queue = g_async_queue_new();
    conf.ready = g_async_queue_new();


    for (n = 0; n < n_threads; n++){
        td[n].thread_id = n + 1;
        td[n].conf = &conf;
        threads[n] = g_thread_create((GThreadFunc)process_queue, &td[n], TRUE, NULL);

        g_async_queue_pop(conf.ready);
    }

    g_async_queue_unref(conf.ready);

    g_message("%d threads created", n_threads);

    add_job(&conf);
    add_job(&conf);
    add_job(&conf);
    add_job(&conf);
    add_job(&conf);
    add_job(&conf);

    for (n = 0; n < n_threads; n++){
        struct job * jb = g_new0(struct job, 1);
        jb->type = JOB_SHUTDOWN;
        g_async_queue_push(conf.queue, jb);
    }

    for (n = 0; n < n_threads; n++)
        g_thread_join(threads[n]);
    
    g_async_queue_unref(conf.queue);
    g_free(td);
    g_free(threads);

    return 0;
}
