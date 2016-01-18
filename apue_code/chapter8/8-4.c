#include "apue.h"
#include "8-3.h"
#include <sys/wait.h>

int main(void)
{
    pid_t pid;
    int status;

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if(pid == 0)
        exit(7);

    if (wait(&status) != pid)
        err_sys("wait error");

    pr_exit(status);

    return 0;
}
