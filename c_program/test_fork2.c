#include "apue.h"

static int glob = 0;

void test()
{
    printf("call test\n");
    glob++;
    printf("%d\n", glob);
}

int child_make(void)
{
    pid_t pid;
    if( 0<(pid=fork())){
        return pid;
    }

    test();

    _exit(0);

}

int main(void)
{
    pid_t pid_arry[2]={-1};
    int i;

    for (i = 0; i < 2; i++){
        pid_arry[i] = child_make();
    }

wait_step:
    wait(NULL);
    for (i = 0; i < 2; i++){
        printf("pid = %d\n", pid_arry[i]);
    }

    if (i >= 2)
        return 0;

    goto wait_step;
    return 0;
}
