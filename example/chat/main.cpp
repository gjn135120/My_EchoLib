#include "ChatServer.h"
using namespace Tiny;


int main(int argc, const char *argv[])
{
	ChatServer server(InetAddr("192.168.150.128", 8899));
	server.start();
	return 0;
}
