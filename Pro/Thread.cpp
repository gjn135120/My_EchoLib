#include "Thread.h"
#include <iostream>
#include <assert.h>
#include <unistd.h>
#include <sys/syscall.h>
using namespace std;

Thread::Thread()
	:_threadId(0),
	 _isRun(false)
{ }

Thread::~Thread()
{
	if(_isRun)
		pthread_detach(_threadId);
}


void *Thread::func(void *arg)
{
	Thread *p = static_cast<Thread *>(arg);
	p->run();
	return NULL;
}


void Thread::start()
{
	pthread_create(&_threadId, NULL, Thread::func, this);
	_isRun = true;
}

void Thread::join()
{
	assert(_isRun);
	pthread_join(_threadId, NULL);
	_isRun = false;
}



