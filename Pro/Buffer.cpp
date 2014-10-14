#include "Buffer.h"
#include "Thread.h"
using namespace std;

Buffer::Buffer(size_t queueSize)
	:_full(_mutex),
	 _empty(_mutex),
	 _queueSize(queueSize)
{

}

bool Buffer::empty() const
{
	MutexLockGuard lock(_mutex);
	return _queue.empty();
}

size_t Buffer::size() const
{
	MutexLockGuard lock(_mutex);
	return _queue.size();
}

void Buffer::push(int val)
{
	{
		MutexLockGuard lock(_mutex);
		while(_queue.size() > _queueSize)
			_empty.wait();
		_queue.push(val);
	}
	_full.notify();
}

int Buffer::pop()
{
	int tmp = 0;
	{
		MutexLockGuard lock(_mutex);
		while(_queue.empty())
			_full.wait();
		tmp = _queue.front();
		_queue.pop();
	}
	_empty.notify();
	return tmp;
}





