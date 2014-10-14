#ifndef RIO_H
#define RIO_H
#include <boost/noncopyable.hpp>
#include <unistd.h>

class Rio : boost::noncopyable
{
public:

	Rio(int fd);
	ssize_t readn(char *usrbuf, size_t count);
	ssize_t readLine(char *usrbuf, size_t len);
	ssize_t writen(int fd, const void *buf, size_t count);

private:
	ssize_t read(char *usrbuf, size_t n);

	static const int kBufferSize = 65536;

	int _fd;
	int _cnt;
	char *_ptr;
 	char _buffer[kBufferSize];
};

#endif  /*RIO_H*/
