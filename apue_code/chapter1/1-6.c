#include "apue.h"
#include <errno.h>

int main(int argc, char *argv[])
{
    //fprintf(stderr, "EACESS: %s\n", strerror(EACCES));
    //errno = ENOENT;
    //
    errno = ECHILD;

    perror(argv[0]);

    exit(0);
}
