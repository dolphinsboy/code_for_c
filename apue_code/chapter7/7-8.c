#include "apue.h"
#include <sys/resource.h>

/**
 * 宏定义中的井号的含义
 * http://www.trueeyu.com/?p=494
 */
#define doit(name) pr_limits(#name, name)

static void pr_limits(char *, int);

int main(void)
{

#ifdef RLIMIT_AS //进程可用存储区的最大总长度，字节
    doit(RLIMIT_AS);
#endif

    doit(RLIMIT_CORE); //core文件的最大字节数，为0阻止创建core文件
    doit(RLIMIT_CPU);//CPU时间的最大量值秒，超过，发送SIGXCPU信号
    doit(RLIMIT_DATA);//数据段的最大字节长度
    doit(RLIMIT_FSIZE); //可以创建的文件的最大字节长度
#ifdef RLIMIT_LOCKS
    doit(RLIMIT_LOCKS); //一个进程可持有的文件锁的最大数
#endif

#ifdef RLIMIT_MEMLOCK
    doit(RLIMIT_MEMLOCK); //一个进程使用mlock能够锁定在存储器中的最大字节长度
#endif

    exit(0);
}

static void pr_limits(char *name, int resource)
{
    struct  rlimit limit;
    unsigned long long lim;
    
    if ( getrlimit(resource, &limit) < 0)
        err_sys("getrlimit error for %s", name);
    printf("%-14s ", name);

    if (limit.rlim_cur == RLIM_INFINITY)
    {
        printf("(infinite) ");
    }else{
        lim = limit.rlim_cur;
        printf("%10lld  ", lim);
    }

    if (limit.rlim_max == RLIM_INFINITY)
    {
        printf("(infinite) ");
    }else
    {
        lim = limit.rlim_max;
        printf("%10lld  ", lim);
    }
    putchar((int)'\n');
    
}

