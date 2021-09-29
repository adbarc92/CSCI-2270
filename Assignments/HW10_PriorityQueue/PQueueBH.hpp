#pragma once

#include "Entry.hpp"

class PQueueBH
{
public:
	PQueueBH();
	~PQueueBH();

	void enqueue(Entry* e);
	Entry* dequeue();
private:
	void rebuildHeap(int i);
	int getParentIndex(int i);
	int getLeftIndex(int i);
	int getRightIndex(int i);
	int size;
	Entry** heap;
};
