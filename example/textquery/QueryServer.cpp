#include "QueryServer.h"
using namespace std;
using namespace std::placeholders;
using namespace Tiny;


QueryServer::QueryServer(const InetAddr &addr, const string &filename)
	:_server(addr),
	 _query(filename),
	 _pool(1000, 4)
{
	_server.setConnectCallback(bind(&QueryServer::onConnection, this, _1));
	_server.setMessageCallback(bind(&QueryServer::onMessage, this, _1));
}

void QueryServer::start()
{
	_pool.start();
	_server.start();
}


void QueryServer::onConnection(const Tiny::TcpConnectionPtr &conn)
{
	conn->send("welcome, please input word : \r\n");
}

void QueryServer::onMessage(const Tiny::TcpConnectionPtr &conn)
{
	string word(conn->recv());

	_pool.addTask(bind(&QueryServer::runQuery, this, word, conn));
}

void QueryServer::runQuery(const std::string &s, const Tiny::TcpConnectionPtr &conn)
{
	string word = s;
	if(word.substr(word.size() - 2, 2) == "\r\n")
	{
		word.erase(word.size() - 1);
		word.erase(word.size() - 1);
	}

	string res = _query.runQuery(word);

	conn->send(res + "\r\n");
}
