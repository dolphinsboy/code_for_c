#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void child_main()
{
    printf("in child\n");

}

void test(pid_t *pid)
{
    *pid = fork();

    if(*pid == 0){
        printf("child = %d\n", getpid());
        child_main();

    }else if(*pid > 0){
        printf("parent = %d\n", getpid());
    }else
        printf("failed to fork");
    
}

int main(void)
{
    int status;
    pid_t pid;

    test(&pid);

    if (waitpid(pid, &status, WUNTRACED | WCONTINUED) < 0){
        printf("failed to waitpid\n");
        exit(1);
    }else{
        printf("child end\n");
        exit(0);
    }
}
