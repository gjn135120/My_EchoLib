#include "Condition.h"
#include "MutexLock.h"
#include <assert.h>

namespace Tiny
{
Condition::Condition(MutexLock &mutex)
    :_mutex(mutex)
{
    TINY_CHECK(!pthread_cond_init(&_cond, NULL));
}

Condition::~Condition()
{
    TINY_CHECK(!pthread_cond_destroy(&_cond));
}

void Condition::wait()
{
	assert(_mutex.isLocked());
    TINY_CHECK(!pthread_cond_wait(&_cond, _mutex.getMutexPtr()));
    _mutex.restoreMutexStatus();
}

void Condition::notify()
{
    TINY_CHECK(!pthread_cond_signal(&_cond));
}

void Condition::notifyAll()
{
    TINY_CHECK(!pthread_cond_broadcast(&_cond));
}
}
