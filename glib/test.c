#include <mysql.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib/gstdio.h>
#include <glib.h>

/*Programe options */
char *hostname = NULL;
guint port = 3306;

char *username = "test";
char *password = "test123";

GOptionEntry common_entries[] ={
    {"host", 'h', 0, G_OPTION_ARG_STRING, &hostname, "The host to connect to", NULL},
    {"port", 'P', 0, G_OPTION_ARG_INT, &port, "TCP/IP port to connect to", NULL},
};

MYSQL *create_main_connection()
{
    MYSQL *conn;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, hostname, username, password, NULL, port, NULL, 0)){
        g_critical("Error connecting to database:%s", mysql_error(conn));
        exit(EXIT_FAILURE);
    }

    return conn;
}

void start_dump(MYSQL *conn)
{
    if (mysql_query(conn, "SHOW PROCESSLIST")){
        g_warning("Could not check PROCESSLIST, no long query guard enabled:%s",
                  mysql_error(conn));
    }else{
        MYSQL_RES *res = mysql_store_result(conn);
        MYSQL_ROW row;

        unsigned int num;
        int i;
        num = mysql_num_fields(res);

        while((row = mysql_fetch_row(res))){
            for (i = 0; i < num; i++){
                if (i < num -1)
                   printf("%s ", row[i] ? row[i] : "NULL");
                else
                   printf("%s\n", row[i] ? row[i] : "NULL");
            }
        }
    }

}

int main(int argc, char *argv[]){
    GError *error = NULL;
    GOptionContext *context;
    context = g_option_context_new("glib option test");

    GOptionGroup *main_group = g_option_group_new("main", 
                                  "Main options", 
                                  "Main options",
                                  NULL, NULL);

    g_option_group_add_entries(main_group, common_entries);
    g_option_context_set_main_group(context, main_group);

    if (!g_option_context_parse(context, &argc, &argv, &error)){
        g_print ("option parsing failed: %s, try --help\n", error->message);
        exit (EXIT_FAILURE);
    }

    MYSQL *conn;
    conn = create_main_connection();
    start_dump(conn);
    g_option_context_free(context);
    return 0;
}
