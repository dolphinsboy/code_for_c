#include "apue.h"
#include <sys/types.h>

#define MAJOR(a) (int)((unsigned short)a >> 8)
#define MINOR(a) (int)((unsigned short)a & 0xFF)

int main(int argc, char *argv[])
{
    int i;
    struct stat buf;

    if (argc < 2){
        err_sys("usage:./a.out <filename>");
        exit(0);
    }

    for ( i = 1; i < argc; i++){

        printf("%s: ", argv[i]);

        if (stat(argv[i], &buf) < 0){
            err_ret("stat error");
            continue;
        }

        printf("dev = %d/%d", MAJOR(buf.st_dev), MINOR(buf.st_dev));
        //针对字符文件或块特殊文件，还会打印该文件的st_rdev值
        if (S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode)){
            printf(" (%s) rdev = %d/%d" ,
                    (S_ISCHR(buf.st_mode)) ? "character" : "block",
                    MAJOR(buf.st_rdev), MINOR(buf.st_rdev));
        }

        printf("\n");
    }

    exit(0);
}
