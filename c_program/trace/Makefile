t:t.c trace.c
	gcc -c t.c trace.c -I ./ -finstrument-functions
	gcc -o t t.o trace.o
clean:
	rm -rf *.o t
