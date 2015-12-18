GLIB_DIR = -I ./glib/include/glib-2.0 -I ./glib/lib/glib-2.0/include
GLIB_LIB = -L ./glib/lib/ -pthread -lgthread-2.0 -lglib-2.0 glib/lib/libglib-2.0.a
MYSQL_LIB = -L/data1/guosong/mysql5616/lib/ -l mysqlclient
MYSQL_INCLUDE = -I /data1/guosong/mysql5616/include

test:test.c
	gcc -g -c test.c $(GLIB_DIR) $(MYSQL_INCLUDE)
	gcc -o test test.o $(GLIB_LIB) $(MYSQL_LIB)


test_glib:test_glib.c
	gcc -g -c -Wall test_glib.c $(GLIB_DIR) 
	gcc -o test_glib test_glib.o $(GLIB_LIB)

util:util.c
	gcc -g -c util.c $(GLIB_DIR) 
	gcc -o util util.o $(GLIB_LIB)
str:string.c
	gcc -g -c string.c $(GLIB_DIR)
	gcc -o str string.o $(GLIB_LIB)

binlog:binlog.c
	gcc -g -c binlog.c $(MYSQL_INCLUDE)
	gcc -o binlog binlog.o $(MYSQL_LIB)

get_config_file:get_config_file.c
	gcc -g -c get_config_file.c $(GLIB_DIR) 
	gcc -o get_config_file get_config_file.o $(GLIB_LIB)

hash_test:hash_test.c
	gcc -g -c hash_test.c $(GLIB_DIR)
	gcc -o hash_test hash_test.o $(GLIB_LIB)

clean:
	rm -rf test test_glib *.o util str binlog get_config_file
