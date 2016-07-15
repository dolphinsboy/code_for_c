#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char buf[BUFSIZ];

    FILE * f = fopen(argv[1], "r");

    if(f == NULL){
        printf("failed to open file");
        exit(0);
    }

    while(fgets(buf, BUFSIZ, f) != NULL){

        if(buf[strlen(buf)-1] == '\n')
            buf[strlen(buf)-1]='\0';

        printf("%s\n", buf);
    }

    return 0;
}
