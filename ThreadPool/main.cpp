#include "ThreadPool.h"
#include <iostream>
#include <time.h>
#include "TimerThread.h"
using namespace Tiny;
void foo()
{
	std::cout << rand() % 100 << std::endl;
}
void stopPool(ThreadPool *a)
{
	a->stop();
}
void nano_sleep(double val);

int main(int argc, const char *argv[])
{
	Tiny::ThreadPool b(120, 4);
	Tiny::TimerThread a(1.0, 0, std::bind(&stopPool, &b));

	b.start();
	a.start();
	while(b.isRunning())
	{
		b.addTask(&foo);
		nano_sleep(0.5);
	}

	a.stop();
	b.stop();

	return 0;
}


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
