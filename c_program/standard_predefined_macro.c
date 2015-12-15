#include <stdio.h>

/*
 * 1-系统操作宏说明
 *  https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html
 *
 * 2-defined说明
 *  https://gcc.gnu.org/onlinedocs/cpp/Defined.html
 */

#if defined(__DATE__) && defined(__TIME__)
    static const char BUILD_DATE[] = __DATE__ " " __TIME__;
#else
    static const char BUILD_DATE[] = "unkown";
#endif

int main(){
    printf("%s\n", BUILD_DATE);

    char arr[] = "aaa" " " "bbb";
    printf("%s\n", arr);

    printf("version=%s\n", VERSION);

    //打印文件名
    printf("FILE=%s\n", __FILE__);
    //打印当前执行的函数名
    printf("PRETTY_FUNCTION=%s\n", __PRETTY_FUNCTION__);

    //打印当前行号
    printf("LINENO=%d\n", __LINE__ - 1);
    return 0;
}
