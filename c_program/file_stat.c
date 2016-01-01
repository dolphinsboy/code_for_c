#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>

#define BUFLEN 28
/*
 *
 *stat 函数帮助:
 * http://pubs.opengroup.org/onlinepubs/009695399/functions/stat.html
 *stat 结构体:
 *http://pubs.opengroup.org/onlinepubs/009695399/basedefs/sys/stat.h.html
 */

char * time_format(time_t t)
{
    char *buff = malloc(BUFLEN);

    struct tm* timeinfo;

    timeinfo = localtime(&t);
    strftime(buff, BUFLEN, "%Y-%m-%d %H:%M:%S", timeinfo);

    return buff;
}

int main()
{
    struct stat conf_s;

    char *conf_path = "./string.c";
    char *p = NULL;

    if(0 != stat(conf_path, &conf_s)){
        printf("read the status of %s failed", conf_path);

        return 1;
    }

    p = time_format(conf_s.st_mtime);
    printf("time=%s\n", p);

    free(p);

}
