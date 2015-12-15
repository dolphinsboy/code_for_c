## code\_for_c
c or c plus code demo/test

###1、Glib

+  glib+mysql
+  glib+thread
+  glib+option
+  glib+log file
+  glib+config file parse
[https://developer.gnome.org/glib/stable/glib-Key-value-file-parser.html#g-key-file-get-value](https://developer.gnome.org/glib/stable/glib-Key-value-file-parser.html#g-key-file-get-value)

**参数修改，且保留注释**
```bash
[guosong@dev-00 glib]$ ./get_config_file test.conf 
group_name=MySQL_Proxy_Layer
key=port, value=4001
key=log_level, value=15
key=log_file, value=./test.log
[guosong@dev-00 glib]$ more test.conf 
[MySQL_Proxy_Layer]
#端口
port=5000
log_level=15
log_file=./test.log
```

Glib相关demo

###2、Getopt
+ getopt参数解析相关的demo
+ argp
+ suboptions

参数解析还有其他的功能:
[http://www.gnu.org/software/libc/manual/html_node/Getopt.html](http://www.gnu.org/software/libc/manual/html_node/Getopt.html)


