#include "MutexLock.h"
#include <assert.h>

MutexLock::MutexLock()
	:_isLock(false)
{
	TINY_CHECK(!pthread_mutex_init(&_mutex, NULL));
}

MutexLock::~MutexLock()
{
	assert(!isLocked());
	TINY_CHECK(!pthread_mutex_destroy(&_mutex));
}

void MutexLock::lock()
{
	TINY_CHECK(!pthread_mutex_lock(&_mutex));
	_isLock = true;
}

void MutexLock::unlock()
{
	_isLock = false;
	TINY_CHECK(!pthread_mutex_unlock(&_mutex));
}
