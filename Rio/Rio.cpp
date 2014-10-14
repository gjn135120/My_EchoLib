#include "Rio.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#define ERR_EXIT(m) \
		do { \
			perror(m);\
			exit(EXIT_FAILURE);\
		}while(0)

Rio::Rio(int fd)
{
	_fd = fd;
	_cnt = 0;
	_ptr = _buffer;
	::memset(_buffer, 0, kBufferSize);
}

ssize_t Rio::read(char *usrbuf, size_t n)
{
	while(_cnt <= 0)
	{
		ssize_t nread = ::read(_fd, _buffer, kBufferSize);
		if(nread == -1)
		{
			if(errno == EINTR)
				continue;
			return -1;
		}
		else if(nread == 0)
			return 0;

		_cnt = nread;
		_ptr = _buffer;
	}

	int cnt = (_cnt < n) ? _cnt : n;
	::memcpy(usrbuf, _ptr, cnt);
	_ptr += cnt;
	_cnt -= cnt;

	return cnt;
}


ssize_t Rio::readn(char *usrbuf, size_t count)
{
	size_t nleft = count;
	ssize_t nread;
	char *buf = (char *)usrbuf;

	while(nleft > 0)
	{
		nread = this->read(buf, nleft);
		if(nread == -1)
		{
			if(errno == EINTR)
				continue;
			return -1;
		}
		else if(nread == 0)
			break;

		nleft -= nread;
		buf += nread;
	}

	return (count - nleft);
}


ssize_t Rio::readLine(char *usrbuf, size_t len)
{
	int i;
	int nread;

	char *buf = usrbuf;
	char c;
	for(i = 0; i < len -1; ++ i)
	{
		if((nread = this->read(&c, 1)) == -1)
			return -1;
		else if(nread == 0)
		{
			if(i == 0)
				return 0;
			break;
		}

		*buf++ = c;
		if(c == '\n')
			break;
	}
	*buf = '\0';
	return i;
}


ssize_t Rio::writen(int fd, const void *buf, size_t count)
{
	size_t nleft = count;
	ssize_t nwrite;
	const char *p = (const char *)buf;
	while(nleft > 0 )
	{
		nwrite = write(fd, p, nleft);
		if(nwrite <= 0)
		{
			if(nwrite == -1)
				if(errno == EINTR)
					continue;
			return -1;
		}

		nleft -= nwrite;
		p += nwrite;
	}

	return count;
}
