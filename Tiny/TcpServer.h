#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <boost/noncopyable.hpp>
#include "EpollPoller.h"
#include "Socket.h"

namespace Tiny
{
class TcpServer : boost::noncopyable
{
public:
	typedef EpollPoller::EpollCallback TcpServerCallback;

	TcpServer(const InetAddr addr);

	void start()
	{ _poller.loop(); }


	void setConnectCallback(TcpServerCallback cb)
	{ _poller.setConnectCallback(std::move(cb)); }

	void setMessageCallback(TcpServerCallback cb)
	{ _poller.setMessageCallback(std::move(cb)); }

	void setCloseCallback(TcpServerCallback cb)
	{ _poller.setCloseCallback(std::move(cb)); }

private:
	Socket _sockfd;
	EpollPoller _poller;
};
}

#endif  /*TCP_SERVER_H*/
