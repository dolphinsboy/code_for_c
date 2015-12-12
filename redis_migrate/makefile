GLIB_INCLUDE = -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include 
REDIS_INCLUDE = -I /home/guosong/code/hiredis-master 
REDIS_LIG = -L /home/guosong/code/hiredis-master

WALL = -Wimplicit-function-declaration -Wunused-variable

redis_migrate:redis_migrate.c
	gcc -g $(WALL) -c redis_migrate.c $(GLIB_INCLUDE) $(REDIS_INCLUDE)
	gcc -o redis_migrate redis_migrate.o  -lglib-2.0  $(REDIS_LIG) -lhiredis
clean:
	rm -rf redis_migrate *.o
