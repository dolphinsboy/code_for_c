FLAG=-DVERSION="\"1.3.2.1\"" 

wc:wc.c
getline:getline.c
getopt:getopt.c
getopt_long:getopt_long.c
standard_predefined_macro:standard_predefined_macro.c
	gcc $(FLAG) -g -c standard_predefined_macro.c
	gcc -o standard_predefined_macro standard_predefined_macro.o

test_snprintf:test_snprintf.c
string:string.c
file_stat:file_stat.c
stdarg_fmt:stdarg_fmt.c
test_time:test_time.c
test_mmap:test_mmap.c
mmap_test1:mmap_test1.c
mmap_A:mmap_A.c
mmap_B:mmap_A.c
mmap_subprocess:mmap_subprocess.c
test_open:test_open.c
test_typedef:test_typedef.c
clean:
	rm -rf *.o wc getline getopt getopt_long \
		standard_predefined_macro test_snprintf file_stat \
		test_time test_mmap mmap_* mmap_subprocess test_open tmp.txt \
		test_typedef
