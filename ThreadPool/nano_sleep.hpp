#ifndef NANO_SLEEP_H
#define NANO_SLEEP_H
#include <time.h>
#include <errno.h>

namespace MyLib
{
void nano_sleep(double val)
{
	struct timespec tv;
    tv.tv_sec = val; //取整
    tv.tv_nsec = (val - tv.tv_sec) * 1000 * 1000 * 1000;

    int ret;
    do
    {
        ret = nanosleep(&tv, &tv);
    }while(ret == -1 && errno == EINTR);
}
}
#endif  /*NANO_SLEEP_H*/
