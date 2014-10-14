#ifndef MUTEXLOCK_H
#define MUTEXLOCK_H

#include "NonCopyable.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#define TINY_CHECK(exp)\
		if(!exp)\
		{	\
			fprintf(stderr, "File : %s, Line : %d Exp : ["#exp"] is true, abort.\n", __FILE__, __LINE__); abort();\
		}



class MutexLock :  NonCopyable
{
	friend class Condition;
public:
	MutexLock();
	~MutexLock();
	void lock();
	void unlock();

	bool isLocked() const { return _isLock; }
	pthread_mutex_t *getMutexPtr() { return &_mutex; }

private:
	void restoreMutexStatus()
	{ _isLock = true; }

	pthread_mutex_t _mutex;
	bool _isLock;
};


class MutexLockGuard : NonCopyable			//将锁封装到MutexLockGuard中，
{											//这样只需定义一个对象，便可
public:										//便可自动上锁，对象销毁时自动解锁
	MutexLockGuard(MutexLock &mutex)
		:_mutex(mutex)
	{ _mutex.lock(); }

	~MutexLockGuard()
	{ _mutex.unlock(); }

private:
	MutexLock &_mutex;
};
#define MutexLockGuard(m) "ERROR"

#endif
