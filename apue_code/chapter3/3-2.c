#include "apue.h"
#include <fcntl.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(void)
{
    int fd;

    if ((fd = creat("file.hole", FILE_MODE)) < 0)
        err_sys("create error");

    if (write(fd, buf1, 10) != 10)
        err_sys("buf1 write error");
    /*offset now = 10 */

    if (lseek(fd, 16384, SEEK_SET) == -1)
        err_sys("lseek error");
    /*offset now = 16384 */
    
    if (write(fd, buf2, 10) != 10)
        err_sys("buf2 write error");
    /*offset now = 16394 */

    exit(0);
}

/*结果展示
 * guosongdeMacBook-Air-3:chapter3 guosong$ ls -lh file.hole
 * -rw-r--r--  1 guosong  staff    16K  1  7 11:51 file.hole
 *  guosongdeMacBook-Air-3:chapter3 guosong$ od -c file.hole
 *  0000000    a   b   c   d   e   f   g   h   i   j  \0  \0  \0  \0  \0  \0
 *  0000020   \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0
 *  *
 *  0040000    A   B   C   D   E   F   G   H   I   J
 *  0040012
*/
