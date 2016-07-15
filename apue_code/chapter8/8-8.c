#include "apue.h"
#include <sys/wait.h>

char *env_init[] = { "USER=unknown", "PATH=/tmp", NULL};

int main(void)
{
    pid_t pid;

    if ((pid = fork()) < 0){
        err_sys("fork error");
    }else if(pid == 0){
        if (execle("/bin/echo", "echo", "myarg1",
                   "MY ARG2", (char *)0, env_init) < 0)
            err_sys("execle error");
    }

    printf("a\n");
    if (waitpid(pid, NULL, 0) < 0)
        err_sys("wait error");

    /*if ((pid = fork()) < 0){
        err_sys("fork error");
    }else if(pid == 0){
        if (execlp("echo", "echo", "only 1 arg", (char *)0) < 0)
            err_sys("excelp error");
    }

    waitpid(pid, NULL, 0);*/

    exit(0);
}
