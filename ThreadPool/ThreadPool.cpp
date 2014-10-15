#include "Thread.h"
#include "ThreadPool.h"
#include <assert.h>
using namespace std;

ThreadPool::ThreadPool(size_t queueSize, size_t poolSize)
	:_full(_mutex),
	 _empty(_mutex),
	 _queueSize(queueSize),
	 _poolSize(poolSize),
	 _isStart(false)
{

}
ThreadPool::~ThreadPool()
{
	if(_isStart)
		stop();
}

void ThreadPool::addTask(Task task)
{
	if(!_isStart)
		return;
	MutexLockGuard lock(_mutex);
	while(_queue.size() >= _queueSize && _isStart)
		_empty.wait();

	if(!_isStart)
		return;

	_queue.push(std::move(task));
	_full.notify();
}

ThreadPool::Task ThreadPool::getTask()
{
	MutexLockGuard lock(_mutex);
	while(_queue.empty() && _isStart)
		_full.wait();

	if(!_isStart)
		return Task();

	assert(!_queue.empty());
	Task task = _queue.front();
	_queue.pop();
	_empty.notify();

	return task;
}

void ThreadPool::runInThread()
{
	while(_isStart)
	{
		Task task(getTask());
		if(task)
			task();
	}
}
void ThreadPool::start()
{
	_isStart = true;

	for(size_t i = 0; i != _poolSize; ++ i)
		_threads.push_back(std::unique_ptr<Thread>(new Thread(std::bind(&ThreadPool::runInThread, this))));

	for(size_t i = 0; i != _poolSize; ++ i)
		_threads[i]->start();
}

void ThreadPool::stop()
{
	if(!_isStart)
		return ;
	{
		MutexLockGuard lock(_mutex);
		_isStart = false;
		while(!_queue.empty())
		_queue.pop();

	}

	_full.notifyAll();
	_empty.notifyAll();

	for(size_t i = 0; i != _poolSize; ++ i)
		_threads[i]->join();



	_threads.clear();
}



