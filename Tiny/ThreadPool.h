#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <boost/noncopyable.hpp>
#include "MutexLock.h"
#include "Condition.h"
#include "Thread.h"
#include <queue>
#include <vector>
#include <memory>
#include <functional>

namespace Tiny
{

class ThreadPool : boost::noncopyable
{
public:
	typedef std::function<void()> Task;

	ThreadPool(size_t queueSize, size_t poolSize);
	~ThreadPool();

	void start();
	void stop();

	void addTask(Task task);
	bool isRunning() const
	{ return _isStart; }

private:
	Task getTask();
	void runInThread();

	mutable MutexLock _mutex;
	Condition _full;
	Condition _empty;
	size_t _queueSize;
	std::queue<Task> _queue;
	const size_t _poolSize;
	std::vector<std::unique_ptr<Thread> > _threads;
	bool _isStart;
};
}

#endif  /*THREAD_POOL_H*/
