#include <stdio.h>

#define MAXLINE 1000

int _getline(char str[], int lim);
void _copy(char to[], char from[]);

int main()
{
    int len;
    int max;

    max = 0;
    char line[MAXLINE];
    char longest[MAXLINE];

    while((len=(_getline(line, MAXLINE))) > max){
        max = len;
        _copy(longest, line);
    }

    printf("MAXLINE=%d, %s\n", max, longest);

    return 0;

}

int _getline(char str[], int lim)
{
    int c;
    int i;

    for ( i = 0; i< lim-1 &&((c=getchar())!=EOF && c != '\n'); i++)
        str[i] = c;

    str[i] = '\0';

    return i;
}

void _copy(char to[], char from[])
{
    int i;

    i = 0;

    while(from[i]!='\0'){
        to[i] = from[i];
        i++;
    }
}
