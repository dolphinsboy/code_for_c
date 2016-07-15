#include <stdio.h>
#include <sys/time.h>

int main(int argc, char **argv){

    struct timeval tv;

    gettimeofday(&tv, NULL);

    long long mill;

    mill = (unsigned long)(tv.tv_sec*1000 + tv.tv_usec/1000);

    printf("mill = %ld\n", mill);

    return 0;
}
