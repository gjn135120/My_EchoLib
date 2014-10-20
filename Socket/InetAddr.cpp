#include "InetAddr.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace Tiny
{
static_assert(sizeof(InetAddr) == sizeof(SAI), "InetAddr Error!!");

InetAddr::InetAddr(uint16_t port)
{
	memset(&_addr, 0, sizeof _addr);
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(port);
	_addr.sin_addr.s_addr = INADDR_ANY;
}

InetAddr::InetAddr (const std::string &ip, uint16_t port)
{
	memset(&_addr, 0, sizeof _addr);
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(port);
	if(inet_aton(ip.c_str(), &_addr.sin_addr) == 0)
	{
		fprintf(stderr, "ip invalid\n");
		exit(EXIT_FAILURE);
	}
}


InetAddr::InetAddr (const SAI &addr)
	:_addr(addr)
{

}


std::string InetAddr::toIp() const
{
	return inet_ntoa(_addr.sin_addr);
}

uint16_t InetAddr::toPort() const
{
	return ntohs(_addr.sin_port);
}

std::string InetAddr::toIpPort() const
{
	char buf[100];
	snprintf(buf, sizeof buf, "%s : %d", toIp().c_str(), toPort());
	return buf;
}
}
