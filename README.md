### 1、 基本功能Demo
c or c plus code demo/test

+ 文件的stat分析,解析修改时间

### 2、Glib

+  glib+mysql
+  glib+thread
+  glib+option
+  glib+log file
+  glib+config file parse
[https://developer.gnome.org/glib/stable/glib-Key-value-file-parser.html#g-key-file-get-value](https://developer.gnome.org/glib/stable/glib-Key-value-file-parser.html#g-key-file-get-value)

**参数修改，且保留注释**
```bash
[guosong@dev-00 glib]$ more test.conf 
[MySQL_Proxy_Layer]
#端口
port            =   4001
log_level       =   15
log_file        =   ./test.log
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

上面的方式会使配置文件的格式变掉，故修改源码：

```c
函数g_key_file_to_data

//进行格式化处理
g_string_append_printf (data_string, "%-15s = %s\n", pair->key, pair->value);

```

```bash
[guosong@dev-00 glib]$ more test.conf 
[MySQL_Proxy_Layer]
#端口
port            = 4001

#日志level
#默认为15
log_level       = 15

#日志文件位置
log_file        = ./test.log
[guosong@dev-00 glib]$ ./get_config_file ./test.conf 
group_name=MySQL_Proxy_Layer
key=port, value=4001
key=log_level, value=15
key=log_file, value=./test.log
[guosong@dev-00 glib]$ more test.conf 
[MySQL_Proxy_Layer]
#端口
port            = 5000

#日志level
#默认为15
log_level       = 15

#日志文件位置
log_file        = ./test.log
```
Glib相关demo

### 3、Getopt
+ getopt参数解析相关的demo
+ argp
+ suboptions

参数解析还有其他的功能:
[http://www.gnu.org/software/libc/manual/html_node/Getopt.html](http://www.gnu.org/software/libc/manual/html_node/Getopt.html)


### 4、APUE相关代码

按照章节梳理APUE各章代码[https://github.com/dolphinsboy/code_for_c/tree/master/apue_code/](https://github.com/dolphinsboy/code_for_c/tree/master/apue_code/)
