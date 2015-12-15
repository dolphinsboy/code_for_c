#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

struct config{
    int port;
    int log_level;
    char *log_file;

};

struct config* get_default_config()
{
    struct config* conf = NULL;

    if ( NULL == (conf = calloc(1, sizeof(struct config))))
    {
        printf("Line=%d, function=%s, no enough memeory\n", 
                __LINE__, __PRETTY_FUNCTION__);

        return NULL;
    }

    conf->port = 3306;
    conf->log_level = 2;
    conf->log_file = "test.log";

    return conf;
}

struct config* get_config_fromfile(char *conf_file)
{
    GKeyFile * key_file;
    GError * gerror = NULL;

    if (NULL == (key_file= g_key_file_new()))
    {
        printf("g_key_file_new return NULL\n");

        return NULL;
    }

    if (FALSE == g_key_file_load_from_file(key_file, conf_file, G_KEY_FILE_KEEP_COMMENTS, &gerror))
    {
        printf("g_key_file_load_from_file false, Error=%s,file=%s\n", gerror->message,conf_file);
        return NULL;
    }

    gsize g_cnt = -1;
    gchar **groups = NULL;

    if ( NULL == (groups = g_key_file_get_groups(key_file, &g_cnt)) || g_cnt <=0 )
    {
        printf("%s has no any group\n", conf_file);
        return NULL;
    }

    gchar **keys;
    gsize keys_len;
    gchar *value;

    int i,j;
    for (i = 0; i < g_cnt; i++)
    {
       printf("group_name=%s\n", groups[i]);
       keys = g_key_file_get_keys(key_file, groups[i],&keys_len, &gerror);

       for( j = 0; j < keys_len; j++){
           value = g_key_file_get_string(key_file, groups[i],keys[j], &gerror); 
           printf("key=%s, value=%s\n", keys[j], value);

           if (strcmp(keys[j], "port") == 0)
           {
               g_key_file_set_int64(key_file, groups[i], keys[j], 5000);
           }
       }
    }

    if (FALSE == g_key_file_save_to_file(key_file, conf_file, &gerror))
    {
        printf("Failed to save, error=%s\n", gerror->message);
    }

}

int main(int argc, char *argv[])
{
    char * conf_file = NULL;
    struct config* conf = NULL;


    if (argc < 2){
        printf("./get_config_file confpath\n");
        exit(0);
    }

    conf_file = argv[1];

    if ( NULL == (conf = get_default_config()))
    {
        printf("get_default_config return null\n");
        exit(1);
    }

    if ( 0 == (conf = get_config_fromfile(conf_file)))
    {
        printf("get_config_fromfile return null\n");
        exit(1);
    }

    return 0;
}
