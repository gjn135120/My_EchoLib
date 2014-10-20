#ifndef QUERY_SERVER_H
#define QUERY_SERVER_H

#include <Tiny/TcpServer.h>
#include <Tiny/ThreadPool.h>
#include "TextQuery.h"

class QueryServer : boost::noncopyable
{
public:
	QueryServer(const Tiny::InetAddr &addr, const std::string &filename);
	void start();


private:
	void onConnection(const Tiny::TcpConnectionPtr &conn);
	void onMessage(const Tiny::TcpConnectionPtr &conn);

	void runQuery(const std::string &s, const Tiny::TcpConnectionPtr &conn);

	Tiny::TcpServer _server;
	TextQuery _query;
	Tiny::ThreadPool _pool;
};

#endif  /*QUERY_SERVER_H*/
