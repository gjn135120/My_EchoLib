#ifndef TIMER_THREAD_H
#define TIMER_THREAD_H
#include <boost/noncopyable.hpp>
#include <functional>
#include "Timer.h"
#include "Thread.h"

class TimerThread : boost::noncopyable
{
public:
	typedef std::function<void()> Callback;
	TimerThread(double val, double interval, Callback cb);

	void start();
	void stop();

private:
	Timer _timer;
	Thread _thread;

};


#endif  /*TIMER_THREAD_H*/
