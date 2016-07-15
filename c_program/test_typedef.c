#include <stdio.h>
#include <stdlib.h>

typedef int MyFunc(int);
static MyFunc myfunc;

int myfunc(int a)
{
    return a+10;
}


int main(void)
{
    int val;

    val = myfunc(10);
    printf("%d\n", val);
}
