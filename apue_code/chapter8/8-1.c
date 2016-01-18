#include "apue.h"

int glob = 6;
char buf[] = "a write to stdout\n";

int main(void)
{
    int var;
    pid_t pid;

    var = 88;

    if (write(STDOUT_FILENO, buf, sizeof(buf) -1) != sizeof(buf) - 1)
        err_sys("write error");
    printf("before fork\n");

    if ((pid = fork()) < 0){
        err_sys("fork error");
    }else if(pid == 0){
        //child
        glob++;
        var++;
    }else{
        sleep(2);
    }

    printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);
    exit(0);
}

/*
 *输出：
 *a write to stdout
 before fork
 子进程输出
 pid = 1305, glob = 7, var = 89
 父进程输出
 pid = 1304, glob = 6, var = 88
 *
 */
