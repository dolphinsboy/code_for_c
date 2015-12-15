#include <stdio.h>

#define OUT 0
#define IN 1

int main(){
    int c, nc, nl, nw, state;

    int idx;
    int ndigit[10] = {0};

    nc = nl = nw = 0;

    state = OUT;

    while( (c=getchar()) !=EOF ){
        nc++;

        if ( c >= '0' && c <= '9')
            ndigit[c - '0'] += 1;

        if (c == '\n')
            nl++;

        if (c == ' ' || c == '\t' || c == '\n')
            state = OUT;
        else if (state == OUT){
            state = IN;
            nw++;
        }

    }

    printf("nc = %d, nl = %d, nw = %d\n", nc, nl, nw);

    for (idx = 0; idx < 10; idx++)
        printf("%d, %d\n", idx, ndigit[idx]);

    

    return 0;
}
