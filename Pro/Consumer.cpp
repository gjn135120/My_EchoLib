#include "Consumer.h"
#include "Buffer.h"
#include <iostream>

Consumer::Consumer(Buffer &buffer)
	:_buffer(buffer)
{

}

void Consumer::run()
{
	while(1)
	{
		int num = _buffer.pop();
		std::cout << "get a num : " << num << std::endl;
		sleep(2);
	}
}
