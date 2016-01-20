#include "apue.h"
#include <errno.h>

static void sig_hup(int signo)
{
    printf("SIGHUP received, pid = %d\n", getpid());
}

static void pr_ids(char *name)
{
    printf("%s: pid = %d, ppid = %d, pgrp = %d, tpgrp = %d\n",
            name, getpid(), getppid(), getpgrp(), tcgetpgrp(STDIN_FILENO));
    fflush(stdout);
}

int main(void)
{
    char c;
    pid_t pid;

    pr_ids("parent");
    TELL_WAIT();

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if(pid > 0){
        TELL_CHILD(pid);
        exit(0);
    }else{
        pr_ids("child");
        WAIT_PARENT();
        signal(SIGHUP, sig_hup);
        kill(getpid(), SIGHUP);

        pr_ids("child");
        if(read(STDIN_FILENO, &c, 1) != 1)
            printf("read error from controlling TTY, errno = %d\n", errno);
        exit(0);
    }
}
