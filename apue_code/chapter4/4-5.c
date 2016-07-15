#include "apue.h"
#include <fcntl.h>

int main(void)
{
    if (open("tempfile", O_RDWR) < 0)
        err_sys("open error");

    if (unlink("tempfile") < 0)
        err_sys("unlink error");

    printf("file unlinked\n");
    sleep(15);

    //内核系统检测到连接数为0，如果为0，就删除该文件的内容

    printf("done\n");
    exit(0);
}
