#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 10

int main(int argc, char * argv[]){

    char *str = (char *)malloc(MAX_LINE);

    snprintf(str, MAX_LINE, "%s", "TESTXXXXXXXXXXXXXXXXXXXXXXXXDDDDDDDDDDDDDDD");

    printf("FILE=%s %s\n",__FILE__, str);

    free(str);

    return 0;
}
