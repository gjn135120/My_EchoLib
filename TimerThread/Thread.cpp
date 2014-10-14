#include "Thread.h"
#include <assert.h>

Thread::Thread(ThreadCallback cb)
	:_threadId(0),
	 _isRun(false),
	 _callback(cb)
{

}

Thread::~Thread()
{
	if(_isRun)
		pthread_detach(_threadId);
}


void Thread::start()
{
	pthread_create(&_threadId, NULL, runInThread, this);
	_isRun = true;
}

void Thread::join()
{
	assert(_isRun);
	pthread_join(_threadId, NULL);
	_isRun = false;
}

void *Thread::runInThread(void *arg)
{
	Thread *p = static_cast<Thread *>(arg);
	p->_callback();
	return NULL;
}
