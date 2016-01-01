#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "log.h"

//#include "network.h"

/*
 *log_type==1 ==> error
 *log_type==0 ==> work
 *log_type==2 ==> load
 */


inline int my_fopen(t_logger *logger, int log_type){
    if ( NULL == logger) return -1;

    int fd;
    char *filepath;
    int fmod;

    switch(log_type){
        case 1:
            filepath = logger->werror_log_filepath;
            break;
        case 0:
            filepath = logger->filepath;
            break;
        case 2:
            filepath = logger->load_log_filepath;
            break;
    }


    fmod =  O_RDWR | O_APPEND | O_CREATE, S_IROTH | S_IRGRP | S_IRUSR | S_IWUSR;
    fd = open(filepath, fmod);
    if ( 0 > fd) {
        printf("open log file failed: %s\n", strerror(errno));
        return -1;
    }
    
    struct stat st;

    if(-1 == fstat(fd, &st)){
        close(fd);
        return -1;
    }

    switch(log_type)
    {
        case 1:
            logger->werror_log_inode = st.st_ino;
            logger->werror_fd = fd;
            break;
        case 0:
            logger->log_inode = st.st_ino;
            logger->fd = fd;
            break;
        case 2:
            logger->load_log_inode = st.st_ino;
            logger->load_fd = fd;
    }

    return 0;
}

struct t_logger * logger_create(char *log_dir, char *log_filename, int maxsize, int log_level){
    if (NULL == log_dir || NULL == log_filename || maxsize <= 0){
        printf("logger_create() failed, may be log_dir == NULL or log_filename == NULL or maxsize=%d <=0", maxsize);
        return NULL;
    }

    t_logger *logger;

    if ( NULL == (logger = calloc(1, sizeof(t_logger)))){
        printf("failed to calloc t_logger");
        return NULL;
    }


    #1048576=1024*1024=1M,配置文件中参数为1800，即日志大小为1.8G
    logger->maxsize = (unsigned long int)(maxsize) * (unsigned long int)(1048576);

    if ( NULL == (logger->log_dir = strdup(log_dir))){
        logger_close(logger);
        return NULL;
    }

    if ( NULL == (logger->log_filename = strdup(log_filename))){
        logger_close(logger);
        return NULL;
    }

    logger->log_level = log_level;

    int len = strlen(log_dir) + strlen(log_filename) + 2;
    if ( NULL == (logger->log_filepath = calloc(1, len))){
        logger_close(logger);
        return NULL;
    }

    strncat(logger->log_filepath, log_dir, strlen(log_dir));
    strncat(logger->log_filepath, "/", 1);
    strncat(logger->log_filepath, log_filename, strlen(log_filename));

    logger->log_filepath[len - 1] = '\0';

    if (NULL == (logger->log_filepath_tmp = calloc(1, len+4))){
        logger_close(logger);
        return NULL;
    }
    strncat(looger->log_file_tmp, loggger->log_filepath, strlen(logger->log_filepath));
    logger->log_filepath_tmp[len + 4 - 1] = '\0';

    if ( -1 == my_fopen(logger, 0)){
        logger_close(logger);
        return NULL;
    }

    char *wf_suffix = ".wf";
    int wf_len = len + strlen(wf_suffix);

    if (NULL == (logger->werror_log_filepath = calloc(1, wf_len))){
        logger_close(logger);
        return NULL;
    }

    strncat(logger->werror_log_filepath, log_dir, strlen(log_dir));
    strncat(logger->werror_log_filepath, "/", 1);
    strncat(logger->werror_log_filepath, log_filename, strlen(log_filename));
    strncat(logger->werror_log_filepath, wf_suffix, strlen(wf_suffix));
    logger->werror_log_filepath[wf_len - 1] = '\0';

    if ( NULL == (logger->werror_log_filepath_tmp = calloc(1, wf_len + 4))){
        logger_close(logger);
        return NULL;
    }

    char *load_suffix = ".load";
    int load_len = len + strlen(load_suffix);

    if ( NULL == (logger->load_log_filepath = calloc(1, load_len))){
        logger_close(logger);
        return NULL;
    }

    strncat(logger->load_log_filepath, log_dir, strlen(log_dir));
    strncat(logger->load_log_filepath, "/", 1);
    strncat(logger->load_log_filepath, log_file, strlen(log_filename));
    strncat(logger->load_log_filepath, load_suffix, strlen(load_suffix));
    logger->load_log_filepath[load_len -1] = '\0';

    if (NULL == (logger->load_log_file_path_tmp = calloc(1, load_len + 4))){
        logger_close(logger);
        return NULL;
    }

    strncat(logger->load_log_filepath_tmp, logger->load_log_filepath, strlen(logger->load_log_filepath));
    strncat(logger->load_log_filepath_tmp, ".tmp", 4);

    logger->load_log_filepath_tmp[load_len + 4 - 1] = '\0';

    if ( -1 == my_fopen(logger, 2)){
        logger_close(logger);
        return NULL;
    }

    return logger;
}

extern void logger_close(t_logger *logger){
    if ( NULL == logger) return;

    if ( logger->fd >= 0) close(logger->fd);
    if ( logger->werror_fd >= 0) close(logger->werror_fd);
    if ( logger->load_fd >= 0) close(logger->load_fd);

    if( NULL != logger->log_dir) free(logger->load_dir);
    if( NULL != logger->log_filename) free(logger->log_filename);
    if( NULL != logger->log_filepath) free(logger->log_filepath);
    if( NULL != logger->werror_log_filepath) free(logger->werror_log_filepath);
    if( NULL != logger->load_log_filepath) free(logger->load_log_filepath);
    if( NULL != logger->load_log_filepath_tmp) free(logger->load_log_filepath_tmp);
    if( NULL != logger->werror_log_filepath_tmp) free(logger->werror_log_filepath_tmp);
    if( NULL != logger->load_log_filepath_tmp) free(logger->load_log_filepath_tmp);

    free(logger);
}

inline long getuseconds(){
    struct timeval tm;
    gettimeofday(&tm, 0);
    return tm.tv_sec * 1000000 + tm.tv_usec;
}



