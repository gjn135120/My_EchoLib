#include "server.h"


int main(int argc, const char *argv[])
{
	Server s(InetAddr("192.168.150.128", 8899));
	s.start();
	return 0;
}
