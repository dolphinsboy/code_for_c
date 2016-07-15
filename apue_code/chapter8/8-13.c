#include "apue.h"
#include "8-3.h"
#include "8-12.h"
#include <sys/wait.h>

int main(void)
{
    int status;

    if ((status = system("date")) < 0)
        err_sys("system() error");

    pr_exit(status);

    if ((status = system("nosuchcommand")) < 0)
        err_sys("system() error");
    pr_exit(status);

    exit(0);
}
