#include "ChatServer.h"
using namespace std;
using namespace Tiny;
using namespace std::placeholders;

ChatServer::ChatServer(const Tiny::InetAddr &addr)
	:_server(addr)
{
	_server.setConnectCallback(bind(&ChatServer::onConnection, this, _1));
	_server.setMessageCallback(bind(&ChatServer::onMessage, this, _1));
	_server.setCloseCallback(bind(&ChatServer::onClose, this, _1));
}


void ChatServer::onConnection(const Tiny::TcpConnectionPtr &conn)
{
	printf("%s\n", conn->toString().c_str());

	if(_clients.size() >= 3)
	{
		conn->send("sorry, too mang clients!!\n");
		conn->shutdown();
	}

	conn->send("hello!!\n");
	_clients.insert(conn);
}


void ChatServer::onMessage(const Tiny::TcpConnectionPtr &conn)
{
	string s(conn->recv());
	string msg = conn->get_peer_addr().toIpPort() + "  says : " + s;

	for(auto it = _clients.begin(); it != _clients.end(); ++ it)
	{
		if(*it != conn)
			(*it)->send(msg);
	}
}


void ChatServer::onClose(const Tiny::TcpConnectionPtr &conn)
{
	printf("%s close\n", conn->toString().c_str());

	_clients.erase(conn);
}
