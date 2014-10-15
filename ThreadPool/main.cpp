#include "ThreadPool.h"
#include "nano_sleep.hpp"
#include <iostream>
#include <time.h>
#include "TimerThread.h"
using namespace std;
using namespace MyLib;
void foo()
{
	cout << rand() % 100 << endl;
}
void stopPool(ThreadPool *a)
{
	a->stop();
}

int main(int argc, const char *argv[])
{
	ThreadPool b(120, 4);
	TimerThread a(1, 0.5, std::bind(&stopPool, &b));
	b.start();
	a.start();
	while(b.isRunning())
	{
		b.addTask(&foo);
		MyLib::nano_sleep(0.5);
	}

	a.stop();

	return 0;
}

