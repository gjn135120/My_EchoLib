#include "TimerThread.h"
#include <stdio.h>
#include <unistd.h>

void foo()
{
	printf("foo\n");
}

int main(int argc, const char *argv[])
{
	TimerThread a(3, 1, &foo);
	a.start();
	sleep(10);
	a.stop();
	return 0;
}
