#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CONFIG_MPL_PORT "port"

void test_string_function1();
void test_string_function2();

int main(int argc, char *argv[])
{

    //test_string_function1();
    test_string_function2();
    return 0;
}

void test_string_function2()
{
    //duplicat a string
    const char *astr= "Test123456789";
    char *p = strdup(astr);
    printf("strdup=%s\n",p);

    //strncat
    char *bstr = (char *)malloc(8);
    strncat(bstr, astr, 8);
    printf("str8cat=%s\n", bstr);

    if(p != NULL)
        free(p);
    if (bstr != NULL)
        free(bstr);

}

void test_string_function1()
{
    const char *astr = "Test";
    const char *bstr = "Test bBB";
    const char *cstr = "DTest";


    //查找astr是否是bstr的开头的一部分
    //The strstr() function finds the first occurrence of the substring needle in the string haystack. 
    //The terminating null bytes ('\0') are not compared.
    //
    //The strcasestr() function is like strstr(), but ignores the case of both arguments.
    printf("strstr=%s\n", strstr(bstr, astr));
    printf("strstr=%s\n", strstr(cstr, bstr));

    const char *a = "test";
    const char *b = "TeSt";

    //比较字符串
    printf("cmp=%d\n",strncasecmp(a, b,4));

    printf("strlen=%d\n", strlen(CONFIG_MPL_PORT));

    //将字符串转换为int
    const char *port = "4002";
    printf("port=%d\n", strtoul(port,NULL, 10));

    char p_str[10];
    snprintf(p_str, 10, "%s","xxddssdddddxxxsssseee");

    printf("%s\n", p_str);

    char a_arr[]="dxxeegassgss";
    char b_arr[5];

    strncpy(b_arr, a_arr, 5);

    printf("strncpy=%s\n", b_arr);
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char *addr = "10.30.6.217:53401";
    char ip[16];
    int port;

    sscanf(addr,"%[^:]:%d", ip, &port);

    printf("ip = %s, port = %d\n", ip, port);

    return 0;
}
