#include <stdio.h>
#include <time.h>
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

int main(int argc, char *argv[])
{
    int useconds = getuseconds();

    printf("useconds=%d\n", useconds);

    return 0;
}
