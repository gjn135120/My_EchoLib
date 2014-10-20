#include "TcpConnection.h"

namespace Tiny
{
TcpConnection::TcpConnection(int sockfd)
	:_sockfd(sockfd),
	 _sockIO(sockfd),
	 _localAddr(Socket::get_local_addr(sockfd)),
	 _peerAddr(Socket::get_peer_addr(sockfd)),
	 _isShutdownWrite(false)
{

}

TcpConnection::~TcpConnection()
{
	if(!_isShutdownWrite)
		shutdown();
}

void TcpConnection::handleConnectCallback()
{
	if(_onConnectCallback)
		_onConnectCallback(shared_from_this());
}

void TcpConnection::handleMessageCallback()
{
	if(_onMessageCallback)
		_onMessageCallback(shared_from_this());
}

void TcpConnection::handleCloseCallback()
{
	if(_onCloseCallback)
		_onCloseCallback(shared_from_this());
}


ssize_t TcpConnection::readn(void *buf, size_t len)
{
	ssize_t ret = _sockIO.readn(buf, len);
	if(ret == -1)
	{
		fprintf(stderr, "TcpConnection readn\n");
		exit(EXIT_FAILURE);
	}

	return ret;
}


ssize_t TcpConnection::writen(const void *buf, size_t len)
{
	ssize_t ret = _sockIO.writen(buf, len);
	if(ret == -1)
	{
		fprintf(stderr, "TcpConnection writen\n");
		exit(EXIT_FAILURE);
	}

	return ret;
}


ssize_t TcpConnection::readline(void *buf, size_t len)
{
	ssize_t ret = _sockIO.readline(buf, len);
	if(ret == -1)
	{
		fprintf(stderr, "TcpConnection readline\n");
		exit(EXIT_FAILURE);
	}

	return ret;
}

std::string TcpConnection::recv()
{
	char str[1024] = {0};
	int ret = readline(str, sizeof str);
	if(ret == 0)
		return std::string();
	else
		return std::string(str);
}


void TcpConnection::send(const std::string &s)
{
	writen(s.c_str(), s.size());
}


std::string TcpConnection::toString() const
{
	char buf[100];
	snprintf(buf, sizeof buf, "%s : %d >> %s : %d",
	         _localAddr.toIp().c_str(),
	         _localAddr.toPort(),
	         _peerAddr.toIp().c_str(),
	         _peerAddr.toPort());

	return buf;
}
}
