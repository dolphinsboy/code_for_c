#include "apue.h"
#include <string.h>
#include <sys/wait.h>

char ** getargs(char *str)
{
    char *args[MAXLINE];
    int i = 0;
    char *pch;

    pch = strtok(str, " ");

    while(pch != NULL){
        args[i++] = pch;
        pch = strtok(NULL, " ");
    }

    return args;
}
int main(void)
{
    char buf[MAXLINE];
    pid_t pid;
    int status;

    printf("%% ");

    while(fgets(buf, MAXLINE, stdin) != NULL){
        if(buf[strlen(buf) -1 ] == '\n')
            buf[strlen(buf) -1 ] = '\0';

        if ((pid = fork()) <0){
            err_sys("fork error");
        }else if(pid == 0){
            //child
            //
            getargs(buf);

            execvp(buf, getargs(buf));
            err_ret("couldn't execute: %s", buf);
            exit(127);
        }

        /*parent*/

        if((pid = waitpid(pid, &status, 0)) < 0)
            err_sys("waitpid error");

        printf("%% ");

    }

    exit(0);
}
