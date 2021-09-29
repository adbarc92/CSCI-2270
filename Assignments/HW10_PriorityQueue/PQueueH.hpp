#pragma once

#include "Entry.hpp"

class PQueueH
{
public:
	PQueueH();
	~PQueueH();

	void enqueue(Entry* e);
	Entry* dequeue();
private:
	int size;
	Entry** list;
};
