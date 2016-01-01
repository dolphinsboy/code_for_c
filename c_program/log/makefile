log.o:log.c
	gcc -g -c log.c

test:test.c log.o
	gcc -g -c test.c
	gcc -o test test.o log.o
