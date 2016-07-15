#include "apue.h"
#include <fcntl.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(void)
{
    int fd;

    if ((fd = creat("file.nohole", FILE_MODE)) < 0)
        err_sys("create error");

    if (write(fd, buf1, 10) != 10)
        err_sys("buf1 write error");
    /*offset now = 10 */

    if (write(fd, buf2, 10) != 10)
        err_sys("buf2 write error");
    /*offset now = 20 */

    exit(0);
}
