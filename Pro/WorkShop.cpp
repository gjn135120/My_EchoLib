#include "WorkShop.h"
#include "Producer.h"
#include "Consumer.h"

WorkShop::WorkShop(size_t bufferSize, size_t producerSize, size_t consumerSize)
	:_bufferSize(bufferSize),
	 _buffer(_bufferSize),
	 _producerSize(producerSize),
	 _consumerSize(consumerSize),
	 _producers(_producerSize, new Producer(_buffer)),
	 _consumers(_consumerSize, new Consumer(_buffer))
{

}

WorkShop::~WorkShop()
{
	for(std::vector<Producer *>::iterator iter = _producers.begin();
	    iter != _producers.end();
	    ++ iter)
	    delete *iter;

	for(std::vector<Consumer *>::iterator iter = _consumers.begin();
	    iter != _consumers.end();
	    ++ iter)
	    delete *iter;
}

void WorkShop::startWork()
{
	for(std::vector<Producer *>::iterator iter = _producers.begin();
	    iter != _producers.end();
	    ++ iter)
	    (*iter)->start();

	for(std::vector<Consumer *>::iterator iter = _consumers.begin();
	    iter != _consumers.end();
	    ++ iter)
	    (*iter)->start();

	for(std::vector<Producer *>::iterator iter = _producers.begin();
	    iter != _producers.end();
	    ++ iter)
	    (*iter)->join();

	for(std::vector<Consumer *>::iterator iter = _consumers.begin();
	    iter != _consumers.end();
	    ++ iter)
	    (*iter)->join();
}
