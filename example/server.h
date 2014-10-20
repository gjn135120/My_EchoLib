#ifndef SERVER_H
#define SERVER_H

#include <boost/noncopyable.hpp>
#include <Socket/TcpServer.h>

class Server : boost::noncopyable
{
public:
	explicit Server(const InetAddr &addr);

	void start()
	{ _server.start(); }
private:
	void onConnection(const TcpConnection::TcpConnectionPtr &conn);

	void onMessage(const TcpConnection::TcpConnectionPtr &conn);

	void onClose(const TcpConnection::TcpConnectionPtr &conn);

	TcpServer _server;
};


#endif  /*SERVER_H*/
