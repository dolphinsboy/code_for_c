#ifndef _redis_migrate_h
#define _redis_migrate_h
enum job_type {JOB_SHUTDOWN, JOB_MIGRATE, JOB_TEST};

struct configuration{
    GAsyncQueue* queue;
    GAsyncQueue* ready;
    GMutex *mutex;

    int done;
};

struct job{
    enum job_type type;
    void *data;
    struct configuration* conf;
};

struct migrate_job{
    char *keyname;
};

struct thread_data{
    guint thread_id;
    struct configuration* conf;
};


#endif
