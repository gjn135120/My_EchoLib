#include "SocketIO.h"
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>

namespace Tiny
{
ssize_t SocketIO::readn(void *buf, size_t len)
{
	size_t left = len;
	ssize_t nread;
	char *p = static_cast<char *>(buf);

	while(left > 0)
	{
		nread = ::read(_sockfd, p, left);
		if(nread == -1)
		{
			if(errno == EINTR)
				continue;
			return -1;
		}
		else if(nread == 0)
			break;

		left -= nread;
		p += nread;
	}

	return len - left;
}


ssize_t SocketIO::writen(const void *buf, size_t len)
{
	size_t left = len;
	ssize_t nwrite;
	const char *p = static_cast<const char *>(buf);

	while(left > 0)
	{
		nwrite = ::write(_sockfd, p, left);
		if(nwrite <= 0)
		{
			if(nwrite == -1 && errno == EINTR)
				continue;
			return -1;
		}

		left -= nwrite;
		p += nwrite;
	}

	return len;
}

ssize_t SocketIO::recv_peek(void *buf, size_t len)
{
	int nread;
	do
	{
		nread = ::recv(_sockfd, buf, len, MSG_PEEK);
	}while(nread == -1 && errno == EINTR);


	return nread;
}

ssize_t SocketIO::readline(void *buf, size_t len)
{
	size_t left = len - 1;
	char *p = static_cast<char *>(buf);
	ssize_t nread;
	size_t sum = 0;
	while(left > 0)
	{
		nread = recv_peek(p, left);
		if(nread <= 0)
			return nread;

		int i;
		for(i = 0; i < nread; ++ i)
		{
			if(p[i] == '\n')
			{
				size_t size = i + 1;
				if(readn(p, size) != static_cast<ssize_t>(size))
					return -1;

				p += size;
				sum += size;
				*p = 0;
				return sum;
			}
		}

		if(readn(p, nread) != nread)
			return -1;

		p += nread;
		sum += nread;
		left -= nread;
	}
	*p = 0;
	return len - 1;
}
}
