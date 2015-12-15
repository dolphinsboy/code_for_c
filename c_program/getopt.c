#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int c;
    int aflag;
    int bflag;

    char *cvalue = NULL;
    char *dvalue = NULL;

    while((c = getopt(argc, argv, "abc:d:")) != -1)
    {
        switch(c){
            case 'a':
                aflag = 1;
                break;
            case 'b':
                bflag = 1;
                break;
            case 'c':
                cvalue = optarg;
                break;
            case 'd':
                dvalue = optarg;
                break;
            case '?':
                if (optopt == 'c')
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                else if ( isprint(optopt))
                    fprintf(stderr, "Unknown option '-%c'.\n", optopt);
                else
                    fprintf(stderr, "Unknown option character '\\x%x'", optopt);

                return 1;

            default:
                abort();
        }
    }
    printf("a = %d, b = %d, cvalue=%s, dvalue=%s\n", aflag, bflag, cvalue,dvalue);

    return 0;
}
