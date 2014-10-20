#ifndef CHAT_SERVER_H
#define CHAT_SERVER_H


#include <Tiny/TcpServer.h>
#include <Tiny/InetAddr.h>
#include <set>

class ChatServer : boost::noncopyable
{
public:
	explicit ChatServer(const Tiny::InetAddr &addr);

	void start()
	{ _server.start(); }

private:

	void onConnection(const Tiny::TcpConnectionPtr &conn);
	void onMessage(const Tiny::TcpConnectionPtr &conn);
	void onClose(const Tiny::TcpConnectionPtr &conn);


	Tiny::TcpServer _server;
	std::set<Tiny::TcpConnectionPtr> _clients;
};

#endif  /*CHAT_SERVER_H*/
