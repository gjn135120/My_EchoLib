#ifndef WORKSHOP_H
#define WORKSHOP_H
#include "NonCopyable.h"
#include "Buffer.h"
#include <vector>
class Producer;
class Consumer;
class WorkShop : NonCopyable
{
public:
	WorkShop(size_t bufferSize, size_t producerSize, size_t consumerSize);

	~WorkShop();
	void startWork();
private:

	size_t _bufferSize;

	Buffer _buffer;
	size_t _producerSize;
	size_t _consumerSize;

	std::vector<Producer *> _producers;
	std::vector<Consumer *> _consumers;
};


#endif  /*WORKSHOP_H*/
