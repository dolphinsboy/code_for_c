#include "apue.h"

#define BUFSIZE 256

int main(void)
{
    char *ptr;
    int size;

    char *pwd = "/Users/guosong/Desktop/Sina/Code/code_for_c/apue_code/chapter4";

    if (chdir(pwd) < 0)
        err_sys("chdir failed");

    ptr = malloc(BUFSIZE);

    if (getcwd(ptr, BUFSIZE) == NULL)
        err_sys("getcwd failed");

    printf("cwd = %s\n", ptr);

    free(ptr);
    exit(0);
}
