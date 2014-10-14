#ifndef TIMER_H
#define TIMER_H
#include <boost/noncopyable.hpp>
#include <functional>
#include <sys/timerfd.h>

class Timer : boost::noncopyable
{
public:

	typedef std::function<void()> TimerCallback;

	Timer(int val, int interval, TimerCallback cb);
	~Timer();

	void start();
	void stop();

private:

	int _timerfd;
	int _val;
	int _interval;
	TimerCallback _callback;
	bool _isStart;
};



#endif  /*TIMER_H*/
