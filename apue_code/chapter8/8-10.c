#include "apue.h"
#include <sys/wait.h>

int main(void)
{
    pid_t pid;
    char *path = "/Users/guosong/Desktop/Sina/Code/code_for_c/apue_code/chapter8/testinterp";

    if ((pid = fork()) < 0){
        err_sys("fork error");
    }else if (pid == 0){
        if (execl(path,"testinterp", "myarg1", "MYARG2", (char *)0) < 0)
            err_sys("execl error");
    }

    if (waitpid(pid, NULL, 0) < 0)
        err_sys("waitpid error");

    exit(0);
}
