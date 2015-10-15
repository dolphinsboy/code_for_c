#include <glib.h>

int main(int argc, char *argv[])
{
    GRand *rand;
    GTimer *timer;

    gint n;
    gint i, j;
    gint x = 0;

    //创建随机数
    rand = g_rand_new();

    for(n=0; n < 20; n++)
    {
        g_print("%d  ", g_rand_int_range(rand, 1, 100));
    }
    g_print("\n");
    g_rand_free(rand);

    //创建计时器
    timer = g_timer_new();
    //开启计时
    g_timer_start(timer);

    for (i=0; i< 10000; i++)
        for (j=0; j < 100000; j++)
            x++;

    //停止计时
    g_timer_stop(timer);

    //计算耗时
    g_printf("%ld\tall:%.2f seconds was used!\n",x, g_timer_elapsed(timer, NULL));
    g_free(timer);

    return 0;
}
