#ifndef TCP_CONNECTION_H
#define TCP_CONNECTION_H

#include <boost/noncopyable.hpp>
#include <memory>
#include <functional>
#include "Socket.h"
#include "SocketIO.h"

namespace Tiny
{
class TcpConnection;
typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;

class TcpConnection : boost::noncopyable,
					  public std::enable_shared_from_this<TcpConnection>
{
public:
	typedef std::function<void(const TcpConnectionPtr &)> TcpConnectionCallback;

	explicit TcpConnection(int sockfd);
	~TcpConnection();

	void setConnectCallback(TcpConnectionCallback cb)
	{ _onConnectCallback = std::move(cb); }

	void setMessageCallback(TcpConnectionCallback cb)
	{ _onMessageCallback = std::move(cb); }

	void setCloseCallback(TcpConnectionCallback cb)
	{ _onCloseCallback = std::move(cb); }


	void handleConnectCallback();
	void handleMessageCallback();
	void handleCloseCallback();


	void shutdown()
	{ _sockfd.shutDownWrite(); _isShutdownWrite = true; }

	ssize_t readn(void *buf, size_t len);
	ssize_t writen(const void *buf, size_t len);
	ssize_t readline(void *buf, size_t len);

	std::string recv();
	void send(const std::string &s);

	const InetAddr &get_localAddr() const
	{ return _localAddr; }

	const InetAddr &get_perrAddr() const
	{ return _peerAddr; }

	std::string toString() const;

private:
	Socket _sockfd;
	SocketIO _sockIO;
	const InetAddr _localAddr;
	const InetAddr _peerAddr;
	bool _isShutdownWrite;

	TcpConnectionCallback _onConnectCallback;
	TcpConnectionCallback _onMessageCallback;
	TcpConnectionCallback _onCloseCallback;
};
}

#endif  /*TCP_CONNECTION_H*/
