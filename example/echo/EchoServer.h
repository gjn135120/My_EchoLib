#ifndef ECHO_SERVER_H
#define ECHO_SERVER_H

#include <boost/noncopyable.hpp>
#include <Tiny/TcpServer.h>
#include <Tiny/InetAddr.h>

class EchoServer : boost::noncopyable
{
public:

	explicit EchoServer(const Tiny::InetAddr &addr);

	void start()
	{ _server.start(); }

private:

	void onConnection(const Tiny::TcpConnectionPtr &conn);
	void onMessage(const Tiny::TcpConnectionPtr &conn);
	void onClose(const Tiny::TcpConnectionPtr &conn);


	Tiny::TcpServer _server;
};


#endif  /*ECHO_SERVER_H*/
