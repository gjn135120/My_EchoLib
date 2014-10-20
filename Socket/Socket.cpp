#include "Socket.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <netdb.h>

namespace Tiny
{
Socket::Socket(int sockfd)
	:_sockfd(sockfd)
{

}

Socket::~Socket()
{
	::close(_sockfd);
}


void Socket::bind(const InetAddr &addr)
{
	if(::bind(_sockfd, (SA*)addr.getSockAddr(), sizeof(addr)) == -1)
	{
		fprintf(stderr, "bind addr error!!\n");
		exit(EXIT_FAILURE);
	}
}

void Socket::listen()
{
	if(::listen(_sockfd, SOMAXCONN) == -1)
	{
		fprintf(stderr, "listen error!!\n");
		exit(EXIT_FAILURE);
	}
}
int Socket::accept()
{
	int fd = ::accept(_sockfd, NULL, NULL);
	if(fd == -1)
	{
		fprintf(stderr, "accept error!!\n");
		exit(EXIT_FAILURE);
	}

	return fd;
}

void Socket::shutDownWrite()
{
	if(::shutdown(_sockfd, SHUT_WR) == -1)
	{
		fprintf(stderr, "shutDownWrite error!!\n");
		exit(EXIT_FAILURE);
	}
}

void Socket::set_reuseaddr(bool on)
{
	int val = on ? 1 : 0;
	if(::setsockopt(_sockfd,
	   				SOL_SOCKET,
	   				SO_REUSEADDR,
	   				&val,
	   				static_cast<socklen_t>(sizeof val)) == -1)
	{
		fprintf(stderr, "set_reuseaddr error!!\n");
		exit(EXIT_FAILURE);
	}
}

void Socket::set_reuseport(bool on)
{
#ifdef SO_REUSEPORT
	int val = on ? 1 : 0;
	int ret = ::setsockopt(_sockfd, SOL_SOCKET, SO_REUSEPORT, &val,
	                       static_cast<socklen_t>(sizeof val));
	if(ret < 0)
	{
		fprintf(stderr, "set_reuseport error!!\n");
		exit(EXIT_FAILURE);
	}
#else
	if(on)
		fprintf(stderr, "set_reuseport is not supported\n", );
#endif
}

void Socket::set_tcpnodelay(bool on)
{
	int val = on ? 1 : 0;
	if(::setsockopt(_sockfd,
	   				IPPROTO_TCP,
	   				TCP_NODELAY,
	   				&val,
	   				static_cast<socklen_t>(sizeof val)) == -1)
	{
		fprintf(stderr, "set_tcpnodelay error!!\n");
		exit(EXIT_FAILURE);
	}
}
void Socket::set_keepalive(bool on)
{
	int val = on ? 1 : 0;
	if(::setsockopt(_sockfd,
	   				SOL_SOCKET,
	   				SO_KEEPALIVE,
	   				&val,
	   				static_cast<socklen_t>(sizeof val)) == -1)
	{
		fprintf(stderr, "set_keepalive error!!\n");
		exit(EXIT_FAILURE);
	}
}



InetAddr Socket::get_local_addr(int sockfd)
{
	SAI addr;
	socklen_t len = sizeof addr;
	if(::getsockname(sockfd, (SA *)&addr, &len) == -1)
	{
		fprintf(stderr, "get_local_addr error!!\n");
		exit(EXIT_FAILURE);
	}

	return InetAddr(addr);
}


InetAddr Socket::get_peer_addr(int sockfd)
{
	SAI addr;
	socklen_t len = sizeof addr;
	if(::getpeername(sockfd, (SA *)&addr, &len) == -1)
	{
		fprintf(stderr, "get_peer_addr error!!\n");
		exit(EXIT_FAILURE);
	}

	return InetAddr(addr);
}
}
