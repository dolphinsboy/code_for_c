GLIB_DIR = -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include

test:test.c
	gcc -g -c test.c $(GLIB_DIR) -I /usr/include/mysql/
	gcc -o test test.o -lglib-2.0 -L/usr/lib64/mysql/ -l mysqlclient


test_glib:test_glib.c
	gcc -g -c -Wall test_glib.c $(GLIB_DIR) 
	gcc -o test_glib test_glib.o -pthread -lgthread-2.0 

clean:
	rm -rf test test_glib *.o
