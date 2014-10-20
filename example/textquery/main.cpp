#include "QueryServer.h"
#include <iostream>
#include <string>
using namespace std;
using namespace Tiny;

int main(int argc, const char *argv[])
{
	QueryServer serevr(InetAddr("192.168.150.128", 8899), "1.txt");
	serevr.start();
	return 0;
}
