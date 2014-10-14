#ifndef THREAD_H
#define THREAD_H

#include "NonCopyable.h"
#include <pthread.h>
#include <sys/types.h>

class Thread : NonCopyable
{
public:
	Thread();
	virtual ~Thread();

	void start();
	void join();

	pthread_t getThreadId() { return _threadId; }
	virtual void run() = 0;

private:
	static void *func(void *arg);

	pthread_t _threadId;
	bool _isRun;
};

#endif
