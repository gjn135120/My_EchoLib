#include "TcpServer.h"

namespace
{
int createSocketFd()
{
	int fd = socket(PF_INET, SOCK_STREAM, 0);
	if(fd == -1)
	{
		perror("createSocketFd");
		exit(EXIT_FAILURE);
	}

	return fd;
}
}


namespace Tiny
{
TcpServer::TcpServer(const InetAddr addr)
	:_sockfd(createSocketFd()),
	 _poller(_sockfd.fd())
{
	_sockfd.set_tcpnodelay(false);
    _sockfd.set_reuseport(true);
    _sockfd.set_reuseaddr(true);
    _sockfd.set_keepalive(false);

    _sockfd.bind(addr);
    _sockfd.listen();
}
}
