#ifndef INETADDR_H
#define INETADDR_H

#include <string>
#include <netinet/in.h>

typedef struct sockaddr_in SAI;
typedef struct sockaddr SA;


namespace Tiny
{
class InetAddr
{
public:
	explicit InetAddr(uint16_t port);
	InetAddr (const std::string &ip, uint16_t port);
	InetAddr (const SAI &addr);

	void setSockAddr(const SAI &addr)
	{ _addr = addr; }
	const SAI *getSockAddr() const
	{ return &_addr; }


	std::string toIp() const;
	uint16_t toPort() const;

	std::string toIpPort() const;
private:
	SAI _addr;
};

}

#endif  /*INETADDR_H*/
