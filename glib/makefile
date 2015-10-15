GLIB_DIR = -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include
GLIB_LIB = -pthread -lgthread-2.0 -lglib-2.0
MYSQL_LIB = -L/usr/lib64/mysql/ -l mysqlclient
MYSQL_INCLUDE = -I /usr/include/mysql/

test:test.c
	gcc -g -c test.c $(GLIB_DIR) $(MYSQL_INCLUDE)
	gcc -o test test.o $(GLIB_LIB) $(MYSQL_LIB)


test_glib:test_glib.c
	gcc -g -c -Wall test_glib.c $(GLIB_DIR) 
	gcc -o test_glib test_glib.o $(GLIB_LIB)

clean:
	rm -rf test test_glib *.o
