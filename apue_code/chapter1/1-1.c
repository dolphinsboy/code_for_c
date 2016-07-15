#include "apue.h"
#include <dirent.h>

int main(int argc, char *argv[])
{
    DIR *dp;
    struct dirent *dirp;

    if (argc != 2)
        err_quit("usage: 1-1 directory_name");

    if ((dp = opendir(argv[1])) == NULL)
        err_sys("can't open %s", argv[1]);

    while ((dirp = readdir(dp)) != NULL){
        struct stat st;

        stat(dirp->d_name, &st);

        printf("name=%s, size=%d\n", dirp->d_name, st.st_size);
    }

    closedir(dp);

    exit(0);
}
