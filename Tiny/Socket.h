#ifndef SOCKET_H
#define SOCKET_H

#include <boost/noncopyable.hpp>
#include "InetAddr.h"


namespace Tiny
{
class Socket : boost::noncopyable
{
public:

	explicit Socket(int sockfd);
	~Socket();

	int fd() const { return _sockfd; }
	void bind(const InetAddr &addr);
	void listen();
	int accept();

	void shutDownWrite();

	void set_reuseaddr(bool on);
	void set_reuseport(bool on);
	void set_tcpnodelay(bool on);
	void set_keepalive(bool on);


	static InetAddr get_local_addr(int sockfd);
	static InetAddr get_peer_addr(int sockfd);

private:
	const int _sockfd;
};
}

#endif  /*SOCKET_H*/
