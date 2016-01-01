#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <sys/time.h>

//获取微秒数
/*
 struct timeval {
 time_t      tv_sec;     // seconds 
 suseconds_t tv_usec;    // microseconds 
 };
*/

inline int getuseconds()
{
    struct timeval tm;

    gettimeofday(&tm, 0);

    return tm.tv_sec * 1000000 + tm.tv_usec;
}

void time_now()
{
    struct tm *tm_ptr;
    time_t the_time;
    (void) time(&the_time);
    char buf[256];
    tm_ptr = localtime(&the_time);

    char *log_file="./dbproxy.log";

    snprintf(buf, 256, "%s.%d%02d%02d%02d%02d%02d", log_file,
            tm_ptr->tm_year + 1900,
            tm_ptr->tm_mon + 1,
            tm_ptr->tm_mday,
            tm_ptr->tm_hour,
            tm_ptr->tm_min,
            tm_ptr->tm_sec);

    printf("buf=%s\n", buf);

    rename(log_file, buf);

}

int main(int argc, char *argv[])
{
    int useconds = getuseconds();
    time_now();

    printf("useconds=%d\n", useconds);

    return 0;
}
