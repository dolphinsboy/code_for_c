#include "apue.h"

#define _IO_UNBUFFERED  __SNBF
#define _IO_LINE_BUF    __SLBF
#define _IO_file_flags  _flags
#define BUFFERSZ(fp)    (fp)->_bf._size

/*原来的程序编译不过，添加上面的内容
 *主要参考的链接:
 *http://www.unix.com/programming/111378-head-file-define-_io_.html
 * */

void pr_stdio(const char *, FILE *);

int main(void)
{
    FILE *fp;

    fputs("enter any character\n", stdout);
    if (getchar() == EOF)
        err_sys("getchar error");
    fputs("one line to standard error\n", stderr);

    pr_stdio("stdin", stdin);
    pr_stdio("stdout", stdout);
    pr_stdio("stderr", stderr);

    if (( fp = fopen("/etc/ntp.conf", "r")) == NULL)
        err_sys("fopen error");

    if (getc(fp) == EOF)
        err_sys("getc error");
    pr_stdio("/etc/ntp.conf", fp);

    exit(0);
}

void pr_stdio(const char *name, FILE *fp)
{
    printf("stream = %s, ", name);

    if (fp->_IO_file_flags & _IO_UNBUFFERED)
        printf("unbuffered");
    else if(fp->_IO_file_flags & _IO_LINE_BUF)
        printf("line buffered");
    else
        printf("fully buffered");

    //在mac中上linux上不同
    printf(", buffer size = %d\n", fp->_bf._size);
}
