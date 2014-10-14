#ifndef CONSUMER_H
#define CONSUMER_H
#include "Thread.h"

class Buffer;
class Consumer : public Thread
{
public:
	Consumer(Buffer &buffer);

	void run();

private:
	Buffer &_buffer;
};

#endif  /*CONSUMER_H*/
