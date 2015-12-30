FLAG=-DVERSION="\"1.3.2.1\"" 

wc:wc.c
	gcc -g -c wc.c
	gcc -o wc wc.o

getline:getline.c
	gcc -g -c getline.c
	gcc -o getline getline.o
getopt:getopt.c
	gcc -g -c getopt.c
	gcc -o getopt getopt.o
getopt_long:getopt_long.c
	gcc -g -c getopt_long.c
	gcc -o getopt_long getopt_long.o

standard_predefined_macro:standard_predefined_macro.c
	gcc $(FLAG) -g -c standard_predefined_macro.c
	gcc -o standard_predefined_macro standard_predefined_macro.o

test_snprintf:test_snprintf.c
	gcc -g -c test_snprintf.c
	gcc -o test_snprintf test_snprintf.o

string:string.c
	gcc -g -c string.c
	gcc -o string string.o

file_stat:file_stat.c
	gcc -g -c file_stat.c
	gcc -o file_stat file_stat.o

clean:
	rm -rf *.o wc getline getopt getopt_long standard_predefined_macro test_snprintf file_stat
