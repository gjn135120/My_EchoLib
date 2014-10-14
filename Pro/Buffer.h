#ifndef BUFFER_H
#define BUFFER_H

#include "NonCopyable.h"
#include "MutexLock.h"
#include "Condition.h"
#include <queue>


class Buffer : private NonCopyable
{
public:

	Buffer(size_t queueSize);

	void push(int val);
	int pop();

	bool empty() const;
	size_t size() const;

private:

	mutable MutexLock _mutex;
	Condition _full;
	Condition _empty;
	size_t _queueSize;
	std::queue<int> _queue;
};


#endif  /*BUFFER_H*/
