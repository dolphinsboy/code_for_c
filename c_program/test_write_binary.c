#include "apue.h"

int main()
{
    float data[10];

    data[1] = 1;
    data[2] = 2.2;
    data[4] = 4.4;

    FILE *fp = fopen("tmp.txt", "w");

    if (fwrite(&data[2], sizeof(float), 4, fp) != 4)
        err_sys("fwrite error");

}
