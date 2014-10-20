#include "TcpServer.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
using namespace Tiny;

void onConnection(const TcpConnectionPtr &conn)
{
    printf("%s\n", conn->toString().c_str());
    conn->send("hello, welcome to Chat Server.\r\n");
}

void onMessage(const TcpConnectionPtr &conn)
{
    std::string s(conn->recv());
    conn->send(s);
}

void onClose(const TcpConnectionPtr &conn)
{
    printf(" %s close\n", conn->toString().c_str());
}

int main(int argc, char const *argv[])
{
    InetAddr addr("192.168.150.128", 8899);
    TcpServer server(addr);
    server.setConnectCallback(&onConnection);
    server.setMessageCallback(&onMessage);
    server.setCloseCallback(&onClose);

    server.start();




    return 0;
}
