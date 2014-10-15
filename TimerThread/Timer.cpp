#include "Timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/timerfd.h>
#include <stdint.h>
#include <poll.h>
#define ERR_EXIT(m) \
		do { \
			perror(m);\
			exit(EXIT_FAILURE);\
		}while(0)
namespace
{
	int createTimer()
	{
		int timerfd = ::timerfd_create(CLOCK_REALTIME, 0);
		if(timerfd == -1)
			ERR_EXIT("create");

		return timerfd;
	}

	void setTimer(int timerfd, double val, double interval)
	{
	    const long SECONDS = 1000 * 1000 * 1000;
		struct itimerspec t;
		memset(&t, 0, sizeof t);
		t.it_value.tv_sec = (time_t)val;
		t.it_value.tv_nsec = (val - (time_t)val) * SECONDS;
		t.it_interval.tv_sec = (time_t)interval;
		t.it_interval.tv_nsec = (interval - (time_t)interval) * SECONDS;
		if(::timerfd_settime(timerfd, 0, &t, NULL) == -1)
			ERR_EXIT("settime");
	}

	void stopTimer(int timerfd)
	{
		setTimer(timerfd, 0, 0);
	}

	void readTimer(int timerfd)
	{
		uint64_t howmany;
		if(::read(timerfd, &howmany, sizeof howmany) != sizeof(howmany))
			ERR_EXIT("read");
	}

}
Timer::Timer(double val, double interval, TimerCallback cb)
	:_timerfd(createTimer()),
	 _val(val),
	 _interval(interval),
	 _callback(std::move(cb)),
	 _isStart(false)
{

}


Timer::~Timer()
{
	if(_isStart)
	{
		stop();
		::close(_timerfd);
	}
}


void Timer::start()
{
	setTimer(_timerfd, _val, _interval);
	_isStart = true;

	struct pollfd pfd;
	pfd.fd = _timerfd;
	pfd.events = POLLIN;

	uint64_t val;
	int ret;
	while(_isStart)
	{
		ret = ::poll(&pfd, 1, 5000);
		if(ret == -1)
		{
			if(errno == EINTR)
				continue;
			ERR_EXIT("poll");
		}
		else if(ret == 0)
		{
			printf("timeout\n");
			continue;
		}

		if(pfd.revents == POLLIN)
		{
			readTimer(_timerfd);
			_callback();
		}
	}
}

void Timer::stop()
{
	_isStart = false;
	stopTimer(_timerfd);
}
