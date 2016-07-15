#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int fd;
    char *msg;

    if (argc != 2)
    {
        printf("usage:./a.out filename\n");
        exit(1);
    }

    fd = open(argv[1], O_RDWR|O_CREAT, S_IRUSR |S_IWUSR | S_IROTH |S_IRGRP);

    if (fd < 0)
    {
        msg = malloc(20);

        strcat(msg, "failed to open ");
        strcat(msg, argv[1]);

        msg[strlen(msg) -1 ] = '\0';
        perror(msg);

        free(msg);
        exit(1);
    }

    return 0;

}
