#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <my_global.h>
#include <mysql.h>
#include <m_ctype.h>
#include <sql_common.h>

char *hostname = "10.75.19.81";
int port = 9001;
char *username = "test";
char *passwd = "test123";

enum Error_Code{
    ERR_OK =0,
    ERR_EOF,
    ERR_FAIL
};

MYSQL *create_main_connection()
{
    MYSQL *conn;

    conn = mysql_init(NULL);

    if(!mysql_real_connect(conn, hostname, username, passwd, NULL, port, NULL, 0)){
        printf("Error connectiong to database:%s", mysql_error(conn));
        exit(EXIT_FAILURE);
    }

    return conn;
}

uchar *net_store_data(uchar *destination, const uchar *source, size_t length)
{
    destination= net_store_length(destination, length);
    memcpy(destination, source, length);
    return destination + length;
}

int register_slave(MYSQL *conn)
{
    uchar buf[1024];
    uchar *pos = buf;
    uchar *unix_sock = 0;
    long default_start_pos = 4;
    
    int server_id = 1;

    int4store(pos, server_id); pos+= 4;
    pos= net_store_data(pos, (uchar*) hostname, strlen(hostname));
    pos= net_store_data(pos, (uchar*) username, strlen(username));
    pos= net_store_data(pos, (uchar*) passwd, strlen(passwd));
    int2store(pos, (uint16) port);

    pos += 2;

    int4store(pos, /* rpl_recovery_rank */ 0);
    pos += 4;
    int4store(pos, 0);
    pos += 4;

    if (simple_command(conn, COM_REGISTER_SLAVE, buf, (size_t)(pos - buf), 0))
        return ERR_FAIL;
    return ERR_OK;
}

void start_dump(MYSQL *conn)
{
    const char *binlog_name = "mysql-bin.000002";
    size_t offset = 107;

    uchar buf[1024];
    char *binlog_pos;
    ushort binlog_flags = 0;
    int server_id = mysql_thread_id(conn) -1000;
    size_t binlog_name_length;
    conn->status = MYSQL_STATUS_READY;
    int4store(buf, offset);
    int2store(buf + 4, binlog_flags);
    int4store(buf + 6, server_id);

    binlog_name_length = strlen(binlog_name);

    memcpy(buf + 10, binlog_name, binlog_name_length);

    simple_command(conn, COM_BINLOG_DUMP, buf, binlog_name_length + 10, 1);
}

int main(int argc, char **argv[])
{
    MYSQL *conn;

    conn = create_main_connection();
    
    if (!register_slave(conn)){
        printf("Succced to Register slave!\n");
        start_dump(conn);
    }
}
