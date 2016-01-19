LIB=/Users/guosong/Desktop/Sina/Code/unix/lib

8-1:8-1.c
8-2:8-2.c
8-4:8-4.c 8-3.h
	gcc -g -c 8-4.c 8-3.h
	gcc -o 8-4 8-4.o
8-5:8-5.c
8-6:8-6.c
8-7:8-7.c
	gcc -g -c 8-7.c
	gcc -o 8-7 8-7.o -L$(LIB) -lapue 
8-7-1:8-7-1.c
	gcc -g -c 8-7-1.c
	gcc -o 8-7-1 8-7-1.o -L$(LIB) -lapue
8-8:8-8.c
8-9:8-9.c
8-10:8-10.c

8-13:8-13.c 8-3.h 8-12.h
	gcc -g -c 8-13.c 8-3.h 8-12.h
	gcc -o 8-13 8-13.o

clean:
	rm -rf *.o
	rm -rf 8-1 8-2 8-4 8-5 \
		8-6 8-7 8-7-1 8-8 8-9 8-10
