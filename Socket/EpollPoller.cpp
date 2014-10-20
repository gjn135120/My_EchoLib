#include "EpollPoller.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>


namespace
{
int createEpollFd()
{
	int efd = ::epoll_create1(0);
	if(efd == -1)
	{
		perror("createEpollFd");
		exit(EXIT_FAILURE);
	}

	return efd;
}

void addEpollFd(int efd, int fd)
{
	struct epoll_event ev;
	ev.data.fd = fd;
	ev.events = EPOLLIN;
	if(epoll_ctl(efd, EPOLL_CTL_ADD, fd, &ev) == -1)
	{
		perror("addEpollFd");
		exit(EXIT_FAILURE);
	}
}

void delEpollFd(int efd, int fd)
{
	struct epoll_event ev;
	ev.data.fd = fd;
	if(epoll_ctl(efd, EPOLL_CTL_DEL, fd, &ev) == -1)
	{
		perror("delEpollFd");
		exit(EXIT_FAILURE);
	}
}

int acceptFd(int lfd)
{
	int pfd = ::accept(lfd, NULL, NULL);
	if(pfd == -1)
	{
		perror("acceptFd");
		exit(EXIT_FAILURE);
	}

	return pfd;
}

ssize_t recv_peek(int fd, void *buf, size_t len)
{
	int ret;
	do
	{
		ret = ::recv(fd, buf, len, MSG_PEEK);
	}while(ret == -1 && errno == EINTR);

	return ret;
}

bool isConnectionClose(int fd)
{
	char buf[1024];
	ssize_t nread = recv_peek(fd, buf, sizeof buf);

	if(nread == -1)
	{
		perror("isConnectionClose");
		exit(EXIT_FAILURE);
	}

	return (nread == 0);
}

}

namespace Tiny
{

EpollPoller::EpollPoller(int lfd)
	:_efd(createEpollFd()),
	 _lfd(lfd),
	 _isLoop(false),
	 _events(1024)
{
	addEpollFd(_efd, _lfd);
}

void EpollPoller::waitEpollFd()
{
	int nread;
	do
	{
		nread = epoll_wait(_efd,
		                   &*_events.begin(),
		                   static_cast<int>(_events.size()),
		                   5000);
	}while(nread == -1 && errno == EINTR);

	if(nread == -1)
	{
		perror("waitEpollFd");
		exit(EXIT_FAILURE);
	}

	else if(nread == 0)
		printf("timeout ...\n");
	else
	{
		if(nread == static_cast<int>(_events.size()))
			_events.resize(_events.size() * 2);

		for(int i = 0; i != nread; ++ i)
		{
			if(_events[i].data.fd == _lfd)
			{
				if(_events[i].events & EPOLLIN)
					handleConnection();
			}
			else
			{
				if(_events[i].events & EPOLLIN)
					handleMessage(_events[i].data.fd);
			}
		}
	}
}




void EpollPoller::handleConnection()
{
	int pfd = acceptFd(_lfd);
	addEpollFd(_efd, pfd);

	std::pair<ConnectionList::iterator, bool> ret;

	TcpConnectionPtr conn(new TcpConnection(pfd));
	conn->setConnectCallback(_onConnectCallback);
	conn->setMessageCallback(_onMessageCallback);
	conn->setCloseCallback(_onCloseCallback);

	ret = _lists.insert(std::make_pair(pfd, conn));
	assert(ret.second == true);
	(void)ret;			//消除ret未使用的warning

	conn->handleConnectCallback();

}


void EpollPoller::handleMessage(int pfd)
{
	bool isClosed = isConnectionClose(pfd);
	ConnectionList::iterator it = _lists.find(pfd);
	assert(it != _lists.end());
	if(isClosed)
	{
		it->second->handleCloseCallback();

		delEpollFd(_efd, pfd);
		_lists.erase(it);
	}

	else
	{
		it->second->handleMessageCallback();
	}
}


void EpollPoller::loop()
{
	_isLoop = true;
	while(_isLoop)
	{
		waitEpollFd();
	}

	printf("Loop quit safely\n");
}


void EpollPoller::unloop()
{
	_isLoop = false;

}
}
