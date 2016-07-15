#include "apue.h"

int glob = 6;
//vfork保证子进程先运行
int main(void)
{
    int var;
    pid_t pid;

    var = 88;
    printf("befor vfork\n");

    if ((pid = vfork()) < 0)
        err_sys("vfork error");
    else if(pid == 0){
        //child
        glob++;
        var++;
        //terminate the calling process
        //_exit(0);
    }

    printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);
    exit(0);
}
