#ifndef SOCKET_IO_H
#define SOCKET_IO_H

#include <boost/noncopyable.hpp>
#include <sys/types.h>

namespace Tiny
{
class SocketIO : boost::noncopyable
{
public:
	explicit SocketIO(int sockfd)
		:_sockfd(sockfd)
	{	}

	ssize_t readn(void *buf, size_t len);
	ssize_t writen(const void *buf, size_t len);
	ssize_t readline(void *buf, size_t len);

private:
	ssize_t recv_peek(void *buf, size_t len);

	const int _sockfd;
};
}

#endif  /*SOCKET_IO_H*/
