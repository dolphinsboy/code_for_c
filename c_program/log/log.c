#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
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
    int fattr;

    switch(log_type){
        case 1:
            filepath = logger->werror_log_filepath;
            break;
        case 0:
            filepath = logger->log_filepath;
            break;
        case 2:
            filepath = logger->load_log_filepath;
            break;
    }


    fmod =  O_RDWR | O_APPEND | O_CREAT ;
    fattr = S_IROTH | S_IRGRP | S_IRUSR | S_IWUSR ;
    fd = open(filepath, fmod, fattr);
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

extern t_logger * logger_create(char *log_dir, char *log_filename, int maxsize, int log_level){
    if (NULL == log_dir || NULL == log_filename || maxsize <= 0){
        printf("logger_create() failed, may be log_dir == NULL or log_filename == NULL or maxsize=%d <=0", maxsize);
        return NULL;
    }

    t_logger *logger;

    if ( NULL == (logger = calloc(1, sizeof(t_logger)))){
        printf("failed to calloc t_logger");
        return NULL;
    }


    //1048576=1024*1024=1M,配置文件中参数为1800，即日志大小为1.8G
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
    strncat(logger->log_filepath_tmp, logger->log_filepath, strlen(logger->log_filepath));
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
    strncat(logger->load_log_filepath, log_filename, strlen(log_filename));
    strncat(logger->load_log_filepath, load_suffix, strlen(load_suffix));
    logger->load_log_filepath[load_len -1] = '\0';

    if (NULL == (logger->load_log_filepath_tmp = calloc(1, load_len + 4))){
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

    if( NULL != logger->log_dir) free(logger->log_dir);
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


inline void my_fclose(t_logger *logger, int log_type){
    switch(log_type){
        case 0:
            if(logger->fd >= 0){
                close(logger->fd);
                logger->fd = -1;
            }
            logger->log_inode=0;
            break;
        case 1:
            if(logger->werror_fd >= 0){
                close(logger->werror_fd);
                logger->werror_fd = -1;
            }
            logger->werror_log_inode = 0;
            break;
        case 2:
            if(logger->load_fd >= 0){
                close(logger->load_fd);
                logger->load_fd = -1;
            }

            logger->load_log_inode = 0;
    }
}


inline int one_log_check(t_logger *logger, const char *log_filename, const int log_fd, const ino_t log_ino)
{
    struct stat st;

    if ( -1 == stat(log_filename, &st)){
        if ( log_fd >= 0 )
            my_fclose(logger, 0);
        if( -1 == my_fopen(logger, 0))
            return -1;
        return 0;
    }else if( st.st_ino != log_ino){
        if ( log_fd >= 0 )
            my_fclose(logger, 0);
        if ( -1 == my_fopen(logger, 0))
            return -1;
        if ( -1 == stat(log_filename, &st))
            return -1;
    }

    if ( st.st_size >= logger->maxsize){
        my_fclose(logger, 0);

        struct tm *tm_ptr;
        time_t the_time;
        char buf[256];
        (void)time(&the_time);
        tm_ptr=localtime(&the_time);
        snprintf(buf, 256, "%s.%d%02d%02d%02d%02d%02d", log_filename, tm_ptr->tm_year + 1900,
                tm_ptr->tm_mon+1, tm_ptr->tm_mday, tm_ptr->tm_hour, tm_ptr->tm_min, tm_ptr->tm_sec);

        rename(log_filename, buf);
        if( -1 == my_fopen(logger, 0))
            return -1;
    }

    return 0;
}

inline int log_check(t_logger *logger, int log_type){
    struct stat st;
    int ret;

    switch(log_type){
        case 0:
            ret = one_log_check(logger, logger->log_filepath, 
                                logger->fd, logger->log_inode);
            break;
        case 1:
            ret = one_log_check(logger, logger->werror_log_filepath,
                                logger->werror_fd, logger->werror_log_inode);
            break;
        case 2:
            ret = one_log_check(logger, logger->load_log_filepath, 
                                logger->load_fd, logger->load_log_inode);
            break;
    }

    return ret;
}


extern void log_write(t_logger *logger, int log_type, int level_num, const char *fmt, ...){
    if ( 0 != log_check(logger, log_type)){
        return;
    }

    if ( ( level_num & logger->log_level) == 0){
        return;
    }

    va_list args;
    va_start(args, fmt);

    char buf[LOG_BUF_SIZE];
    bzero(buf, LOG_BUF_SIZE);

    struct timeval time;
    gettimeofday(&time, 0);

    time_t t = time.tv_sec;
    struct tm*tm = localtime(&t);

    snprintf(buf, sizeof(buf), "[%d-%02d-%02d %02d:%02d:%02d.%06ld]",
             1900 + tm->tm_year, 1 + tm->tm_mon,
             tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec, time.tv_usec);
    vsnprintf(buf + strlen(buf), sizeof(buf) - strlen(buf) - 2, fmt, args);

    buf[LOG_BUF_SIZE - 1] = '\x00';

    int fd = (log_type == 1) ? logger->werror_fd:(log_type == 0) ? logger->fd : logger->load_fd;
    write(fd, buf, strlen(buf));
    va_end(args);
}

void log_work(t_logger *logger, int type)
{
    log_write(logger, 0, 0x04, " %s\n", "Hello Log XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
}

/*void log_work(t_logger *logger, network_socket *client, int type){
    if(client == NULL || (client->is_client_socket == 0 && client->server == NULL)){
        log_error(logger, "log work failed, client == NULL");
        return;
    }

    if(client->is_client_socket == 0){
        client = client->client;
    }

    network_socket *server = client->server;
    char *c_ip = client->ip[0] == '\0' ? "unknow" : client->ip;
    int c_port = client->port;
    char *c_username = client->p_user == NULL ? "" : client->p_user->username;
    char *s_ip = server == NULL || server->db == NULL ? "self" : server->db->addr.addr_name;
    int s_port = server == NULL || server->db == NULL ? -1 : server->db->addr.port;
    int s_thread_id = server == NULL ? -1 :server->handshake.thread_id;
    gunit64 affected_row = client->result.qstatus.affected_rows;
    gunit64 packet_size = client->result.result_set_size;

    if(client->query.result_read_time.tv_sec < client->query.query_send_time.tv_sec ||
            (client->query.result_read_time.tv_sec == client->query.query_sent_time.tv_sec &&
             client->query.result_read_time.tv_usec < client->query.query_sent_time.tv_usec))
        client->query.result_read_time = client->query.query_sent_time;

    long query_sent_us = (client->query.query_sent_time.tv_sec - client->query.start_time.tv_sec) * 1000000
        + client->query.query_sent_time.tv_usec - client->query.start_time.tv_usec;

    if(query_sent_us<0)
        query_sent_us = 0;

    long result_read_us = (client->query.result_read_time.tv_sec - client->query.query_sent_time.tv_sec) * 1000000 + client->query.end_time.tv_usec - client->query.result_read_time.tv_usec;

    if(result_sent_us < 0)
        result_sent_us = 0;

    long total_cost_us = query_sent_us + result_read_us + result_sent_us;

    char log_cmd[MAX_LOG_SQL_LEN];

    char *str_type;

    if(type == LOG_WORK_TYPE_CONN){
        str_type = "CONN";
        total_cost_us = result_sent_us = result_read_us = query_sent_us = 0;
        affected_rows = packet_size = 0;
        snprintf(log_cmd, MAX_LOG_SQL_LEN, "%s", "connect");
    }else if(type == LOG_WORK_TYPE_QUIT){
        str_type = "QUIT";
        total_cost_us = result_sent_us = result_read_us = query_sent_us = 0;
        affected_rows = packet_size = 0;
        snprintf(log_cmd, MAX_LOG_SQL_LEN, "%s", "quit");
    }else{
        str_type = "QURY";
        if(client->query.query_command == "\x03" || client->query.command == '\x16')
            truncate_str_two_ends(log_cmd, client->query.args, client->query.args_len-1);
        else
            snprintf(log_cmd, MAX_LOG_SQL_LEN, "COMMAD=%ld",client->query.command);
    }
    // [client_ip:client:port:client_thread_id:product_user][server_ip:server_port:server_thread_id]
    // [time1/time2/time3/time_total/unused_field][rows/pack_size/unused_field/unused_field/unused_field]
    // [unused_field] SQL
    //

    log_write(logger, 0, 0x04, "[%s][%s:%d:%d:%s][%s:%d:%d][%ld/%ld/%ld/%ld/%d][%d/%d/%d/%d/%d][%s] %s\n",
            str_type, c_ip, c_port, 0, c_username, s_ip, s_port, s_thread_id, query_sent_us, result_read_us,
            result_client_us, total_cost_us, 0, affected_rows, packet_size, 0, 0, 0, "",log_cmd);

}
*/
