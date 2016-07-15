#include "apue.h"
#include <fcntl.h>

#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

int main(void)
{
    umask(0);

    if (creat("foo", RWRWRW) < 0)
        err_sys("create error for foo");

    umask(S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
    if (creat("bar", RWRWRW) < 0)
        err_sys("create error for bar");
    exit(0);
}

/*
 * -rw-------  1 guosong  staff     0B  1 11 16:19 bar
 * -rw-rw-rw-  1 guosong  staff     0B  1 11 16:19 foo
 */
