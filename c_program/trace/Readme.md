### 使用addr2line分析代码和函数的对应位置

[guosong@dev-00 15:10:44 20170602]$./t
ENTER: 0x4005e2, from 0x7ff91568e7d5
ENTER: 0x4005a9, from 0x40060d
EXIT:  0x4005a9, from 0x40060d
ENTER: 0x400570, from 0x400619
EXIT:  0x400570, from 0x400619
foo=2 bar=1
EXIT:  0x4005e2, from 0x7ff91568e7d5
[guosong@dev-00 15:10:45 20170602]$addr2line 0x400570 -e ./t -f         
foo
/home/guosong/opdir/20170602/t.c:3
[guosong@dev-00 15:12:32 20170602]$addr2line  0x4005e2 -e ./t -f         
main
/home/guosong/opdir/20170602/t.c:11
[guosong@dev-00 15:12:41 20170602]$addr2line 0x4005a9 -e ./t -f          
bar
