#include <signal.h>
#include <unistd.h>

static void sig_alrm(int signo)
{

}

unsigned int sleep1(unsigned int nsecs)
{
    if (signal(SIGALRM, sig_alrm) == SIG_ERR)
        return (nsecs);
    alarm(nsec);

    pause();

    return (alarm(0));

}

