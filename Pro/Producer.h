#ifndef PRODUCER_H
#define PRODUCER_H
#include "Thread.h"

class Buffer;

class Producer : public Thread
{
public:
	Producer(Buffer &buffer);

	void run();
private:
	Buffer &_buffer;
};

#endif  /*PRODUCER_H*/
