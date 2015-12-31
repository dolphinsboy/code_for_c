#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

/*
 *help:
 *http://en.cppreference.com/w/c/variadic
 */
void simple_printf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    while(*fmt != '\0'){
        if (*fmt == 'd'){
            int i = va_arg(args, int);
            printf("%d\n", i);
        }else if (*fmt == 'c'){
            int c = va_arg(args, int);
            printf("%c\n", c);
        }else if(*fmt == 'f'){
            double d = va_arg(args, double);
            printf("%f\n",d);
        }else if(*fmt == 's'){
            char *p = va_arg(args, char*);
            printf("%s\n", p);
        }

        ++fmt;
    }

    va_end(args);
}

int main(void)
{
    simple_printf("dcffs", 3, 'a', 1.999, 42.5, "hello world");
}
