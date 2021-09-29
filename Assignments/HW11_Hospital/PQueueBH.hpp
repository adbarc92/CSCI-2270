#pragma once

#include "PQueueHelper.hpp"

class PQueueBH
{
public:
	PQueueBH( );
	~PQueueBH();
	Patient* dequeue();
	void enqueue( Patient* );
private:
	void rebuildHeap( int i );
	int getParentIndex( int i );
	int getLeftIndex( int i );
	int getRightIndex( int i );
	int size;
	Patient** heap;
};

// Could add peek