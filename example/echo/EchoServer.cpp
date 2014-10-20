#include "EchoServer.h"
using namespace std;
using namespace Tiny;
using namespace std::placeholders;

EchoServer::EchoServer(const Tiny::InetAddr &addr)
	:_server(addr)
{
	_server.setConnectCallback(bind(&EchoServer::onConnection, this, _1));
	_server.setMessageCallback(bind(&EchoServer::onMessage, this, _1));
	_server.setCloseCallback(bind(&EchoServer::onClose, this, _1));
}


void EchoServer::onConnection(const Tiny::TcpConnectionPtr &conn)
{
	printf("%s\n", conn->toString().c_str());
	conn->send("hello!!\n");
}

void EchoServer::onMessage(const Tiny::TcpConnectionPtr &conn)
{
	string s(conn->recv());
	conn->send(s);
}

void EchoServer::onClose(const Tiny::TcpConnectionPtr &conn)
{
	printf("%s close\n", conn->toString().c_str());
}
