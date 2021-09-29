#include <iostream>
#include <sstream>

#include "Queue.h"

Queue::Queue( int sz )
{
	queueSize = sz;
	queueHead = 0;
	queueTail = 0;
	queueCount = 0;
	arrayQueue = new std::string[ sz ];
}

Queue::~Queue()
{
	delete [] arrayQueue;
	arrayQueue = nullptr;
}

void Queue::enqueue( std::string word )
{
	if( queueIsFull() )
	{
		std::cout << "Queue is full." << std::endl;
		return;
	}

	arrayQueue[ queueTail ] = word;
	queueTail = ( queueTail + 1 ) % queueSize;
	queueCount++;

	std::cout << "E: " << word << std::endl;
	std::cout << "H: " << queueHead << std::endl;
	std::cout << "T: " << queueTail << std::endl;
}

void Queue::dequeue()
{
	if( queueIsEmpty() )
	{
		std::cout << "Queue is empty." << std::endl;
		return;
	}

	std::string word = arrayQueue[ queueHead ];
	queueHead = ( queueHead + 1 ) % queueSize;
	queueCount--;

	std::cout << "H: " << queueHead << std::endl;
	std::cout << "T: " << queueTail << std::endl;
	std::cout << "word: " << word << std::endl;
}

void Queue::printQueue()
{
	if( queueIsEmpty() )
	{
		std::cout << "Empty" << std::endl;
		return;
	}

	for( int i = 0; i < queueCount; i++ )
	{
		int ind = ( queueHead + i ) % queueSize;
		std::cout << ind << ": " << arrayQueue[ ind ] << std::endl;
	}
}

void Queue::enqueueSentence( std::string sen )
{
	std::string word;
	std::stringstream ss( sen );
	while( std::getline( ss, word, ' ' ) )
	{
		enqueue( word );
	}
}

bool Queue::queueIsFull()
{
	return queueCount >= queueSize;
}

bool Queue::queueIsEmpty()
{
	return queueCount == 0;
}