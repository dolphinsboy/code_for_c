#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

void  print_pair(gpointer key, gpointer value, gpointer user_data)
{
    printf("key=%s, value=%s\n", key, value);

}

int main(int argc, char *argv[])
{
    GHashTable* ht;

    if ( NULL == (ht = g_hash_table_new(g_str_hash, g_str_equal))){
        printf("g_hash_table_new return null\n");
        exit(1);
    }

    g_hash_table_insert(ht, "A","1");
    g_hash_table_insert(ht, "B","2");
    g_hash_table_insert(ht, "C","3");
    g_hash_table_insert(ht, "D","4");

   g_hash_table_foreach(ht, print_pair, NULL);

   char *p = g_hash_table_lookup(ht, "C");

   if(p!=NULL){
       printf("value=%s\n", p);
   }

    return 0;
}
