#ifndef TIMER_H
#define TIMER_H
#include <boost/noncopyable.hpp>
#include <functional>
#include <sys/timerfd.h>

class Timer : boost::noncopyable
{
public:

	typedef std::function<void()> TimerCallback;

	Timer(double val, double interval, TimerCallback cb);
	~Timer();

	void start();
	void stop();

private:

	int _timerfd;
	double _val;
	double _interval;
	TimerCallback _callback;
	bool _isStart;
};



#endif  /*TIMER_H*/
