LIB=/Users/guosong/Desktop/Sina/Code/unix/lib

14-1:14-1.c 
	gcc -g -c 14-1.c
	gcc -o 14-1 14-1.o -L$(LIB) -lapue
14-4:14-4.c
	gcc -g -c 14-4.c
	gcc -o 14-4 14-4.o -L$(LIB) -lapue

14-6:14-6.c
	gcc -g -c 14-6.c
	gcc -o 14-6 14-6.o -L$(LIB) -lapue

14-8:14-8.c
14-10:14-10.c

test_epoll:test_epoll.c

14-12:14-12.c

clean:
	rm -rf *.o
	rm -rf 14-1 14-4 14-6 test_epoll 14-12
