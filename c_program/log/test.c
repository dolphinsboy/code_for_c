#include "log.h"

int main(int argc, char *argv[])
{
    char *log_dir = "./log";
    char *log_filename = "test.log";
    int maxsize = 1;
    int log_level = 14;

    logger = logger_create(log_dir, log_filename, maxsize, log_level);

    if (logger == NULL)
    {
        printf("%s:%s:%d create log failed.\n", 
                __FILE__, __PRETTY_FUNCTION__,
                __LINE__);
        return 1;
    }

    log_work(logger, 1);

    return 0;



}
