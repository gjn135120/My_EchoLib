#include "TimerThread.h"
#include "nano_sleep.hpp"
#include <stdio.h>
#include <unistd.h>
using namespace MyLib;
void foo()
{
	printf("foo\n");
}

int main(int argc, const char *argv[])
{
	TimerThread a(0.5, 0.5, &foo);
	a.start();
	MyLib::nano_sleep(2);
	a.stop();
	return 0;
}
