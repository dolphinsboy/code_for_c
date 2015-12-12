## code\_for_c
c or c plus code demo/test

###1、Glib

+  glib+mysql
+  glib+thread
+  glib+option
+  glib+log file

Glib相关demo

###2、Redis_Migrate

参照mydumper的代码实现redis_migrate的功能，主要使用如下库：

+ Glib
+ hiredis-master

由于redis的python client不支持migrate的命令，需要通过echo xx |redis-cli的方式实现，而hiredis-master支持，且可以使用一个长连接，故基于此写了这个代码。

```c
GLIB_INCLUDE = -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include 
REDIS_INCLUDE = -I /home/guosong/code/hiredis-master 
REDIS_LIG = -L /home/guosong/code/hiredis-master

WALL = -Wimplicit-function-declaration -Wunused-variable

redis_migrate:redis_migrate.c
        gcc -g $(WALL) -c redis_migrate.c $(GLIB_INCLUDE) $(REDIS_INCLUDE)
        gcc -o redis_migrate redis_migrate.o  -lglib-2.0  $(REDIS_LIG) -lhiredis
clean:
        rm -rf redis_migrate *.o
```
