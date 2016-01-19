#include "apue.h"

static void charatatime(char *);

int main(void)
{
    pid_t pid;

    TELL_WAIT();
    
    if ((pid = fork()) < 0){
        err_sys("fork error");
    }else if(pid == 0){
        charatatime("output from child\n");
        TELL_PARENT(getppid()); //父进程先行
    }else{
        WAIT_CHILD();
        charatatime("output from parent\n");
    }

    exit(0);
}

static void charatatime(char *str)
{
    char *ptr;
    int c;
    //set unbuffered
    setbuf(stdout, NULL);

    for (ptr = str; (c = *ptr++) != 0; )
        putc(c, stdout);
}
