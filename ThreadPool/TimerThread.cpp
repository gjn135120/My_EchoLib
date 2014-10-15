#include "TimerThread.h"

TimerThread::TimerThread(double val, double interval, Callback cb)
	:_timer(val, interval, std::move(cb)),
	 _thread(std::bind(&Timer::start, &_timer))
{

}

void TimerThread::start()
{
	_thread.start();
}

void TimerThread::stop()
{
	_timer.stop();
	_thread.join();
}
