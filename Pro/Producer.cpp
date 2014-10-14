#include "Producer.h"
#include "Buffer.h"
#include <iostream>
#include <stdlib.h>


Producer::Producer(Buffer &buffer)
	:_buffer(buffer)
{
	srand(12345);
}
void Producer::run()
{
	while(1)
	{
		int num = rand() % 100;
		std::cout << "push a num : " << num << std::endl;
		_buffer.push(num);

		sleep(2);
	}
}
