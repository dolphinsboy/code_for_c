#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

guint str_hash(char *v) {
    /* 31 bit hash function */
    const signed char *p = v; 
    guint32 h = *p;
    if (h){ 
        for (p += 1; *p != '\0'; p++){
            h = (h << 5) - h + *p;
        }
    }    
    return h;
}

int main(int argc, char *argv[])
{
    char *db="10.75.19.79";
    printf("hash_value=%d\n", str_hash(db));
}
