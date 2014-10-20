#include "server.h"

Server::Server(const InetAddr &addr)
	:_server(addr)
{
	_server.setConnectCallback(bind(&Server::onConnection, this, _1));
	_server.setMessageCallback(bind(&Server::onMessage, this, _1));
	_server.setCloseCallback(bind(&Server::onClose, this, _1));
}


void Server::onConnection(const TcpConnection::TcpConnectionPtr &conn)
{
    printf("%s\n", conn->toString().c_str());
    conn->send("hello, welcome to Chat Server.\r\n");
}

void Server::onMessage(const TcpConnection::TcpConnectionPtr &conn)
{
    std::string s(conn->recv());
    conn->send(s);
}

void Server::onClose(const TcpConnection::TcpConnectionPtr &conn)
{
    printf("client close\n");
}
