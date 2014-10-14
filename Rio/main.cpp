#include "Rio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
using namespace std;

int main(int argc, const char *argv[])
{
	int fd = open("1.txt", O_WRONLY);
	char buf[1024];
	Rio a(fd);
	int i;
	while(memset(buf, 0, sizeof(buf)), scanf("%s", buf))
	{
		i = a.writen(fd, (void*)buf, strlen(buf));
		printf("%d\n", i);
	}
	return 0;
}
