#ifndef EPOLL_POLLER_H
#define EPOLL_POLLER_H

#include <boost/noncopyable.hpp>
#include <vector>
#include <map>
#include <sys/epoll.h>
#include "TcpConnection.h"

namespace Tiny
{
class EpollPoller : boost::noncopyable
{
public:

	typedef TcpConnection::TcpConnectionCallback EpollCallback;

	explicit EpollPoller(int lfd);
	~EpollPoller()
	{ ::close(_efd); }

	void loop();
	void unloop();



	void setConnectCallback(EpollCallback cb)
	{ _onConnectCallback = std::move(cb); }

	void setMessageCallback(EpollCallback cb)
	{ _onMessageCallback = std::move(cb); }

	void setCloseCallback(EpollCallback cb)
	{ _onCloseCallback = std::move(cb); }

private:
	void waitEpollFd();
	void handleConnection();
	void handleMessage(int pfd);

	const int _efd;
	const int _lfd;
	bool _isLoop;

	typedef std::vector<struct epoll_event> EventList;
	EventList _events;

	typedef std::map<int, TcpConnectionPtr> ConnectionList;
	ConnectionList _lists;

	EpollCallback _onConnectCallback;
	EpollCallback _onMessageCallback;
	EpollCallback _onCloseCallback;
};
}


#endif  /*EPOLL_POLLER_H*/
