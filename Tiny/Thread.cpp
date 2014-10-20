#include "Thread.h"
#include <assert.h>
#include "MutexLock.h"
using namespace Tiny;

Thread::Thread(ThreadCallback cb)
	:_threadId(0),
	 _isRun(false),
	 _callback(std::move(cb))
{

}

Thread::~Thread()
{
	if(_isRun)
		TINY_CHECK(!pthread_detach(_threadId));
}


void Thread::start()
{
	TINY_CHECK(!pthread_create(&_threadId, NULL, runInThread, this));
	_isRun = true;
}

void Thread::join()
{
	assert(_isRun);
	TINY_CHECK(!pthread_join(_threadId, NULL));
	_isRun = false;
}

void *Thread::runInThread(void *arg)
{
	Thread *p = static_cast<Thread *>(arg);
	p->_callback();
	return NULL;
}
