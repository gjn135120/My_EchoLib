#ifndef CONDITION_H
#define CONDITION_H

#include <pthread.h>
#include "NonCopyable.h"

class MutexLock;


class Condition : NonCopyable
{
public:
    Condition(MutexLock &mutex);
    ~Condition();

    void wait();
    void notify();
    void notifyAll();
private:
    pthread_cond_t _cond;
    MutexLock &_mutex;
};

#endif
