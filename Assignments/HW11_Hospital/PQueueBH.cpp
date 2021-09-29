#include "PQueueBH.hpp"

#include <stdexcept>
#include <iostream>

PQueueBH::PQueueBH() // Sets standard object member sizes
{
	size = 0;
	heap = nullptr;
}

PQueueBH::~PQueueBH() // Delete the heap/array
{
	delete [] heap;
}

void PQueueBH::enqueue( Patient* p ) // Input: Entry/Patient; 
{
	size++; // First, increase size
	Patient** newHeap = new Patient*[ size ]; // Dynamically create new heap
	memcpy(newHeap, heap, ( size - 1 ) * sizeof( Patient* ) ); // Copy block of memory (Destination, Source, Number bytes copied)
	// Size = OriginalSize * PatientSize; should copy all memory contents to a newHeap of greater size

	int i = size - 1; // New integer for index, at last slot of heap
	// Could make changes for different implementation
	int parentI = getParentIndex( i );
	newHeap[ i ] = p; // Enqueue to newHeap

	while( shouldComeBefore( p, newHeap[ parentI ] ) && i > 0 ) // If new patient should come before parent, swap with parent
	{
		Patient* tmp = newHeap[ i ];
		newHeap[ i ] = newHeap[ parentI ];
		newHeap[ parentI ] = tmp;
		i = parentI; // Because spots have been swapped, child is parent;
		parentI = getParentIndex( i ); // To ensure that parentI now points to i's current parent
	}

	if ( heap != nullptr ) // If old heap exists, delete
	{
		delete [] heap;
	}
	heap = newHeap;
}

Patient* PQueueBH::dequeue()
{
	if ( size <= 0 )
	{
		throw -1;
	}
	
	Patient* ret = heap[ 0 ]; // Would be -1 if using book implementation
	heap[ 0 ] = heap[ size - 1 ]; // Replaces first entry with last - why?
	size--; // Reduce size accordingly

	if ( size == 0 ) // If heap is now empty
	{
		delete [] heap; // Delete heap
		heap = nullptr; // Heap is now null
		return ret; // Return patient
	}

	Patient** newHeap = new Patient*[ size ]; // Create new heap of adjusted size
	memcpy( newHeap, heap, size * sizeof( Patient* ) );
	delete [] heap;
	heap = newHeap; // New heap replaces old heap
	rebuildHeap( 0 ); // Heapify

	return ret;
}

void PQueueBH::rebuildHeap( int i ) // Analogous to MinHeaify
{
	int left = getLeftIndex( i );
	int right = getRightIndex( i );
	int smallest = i;

	if ( left < size && shouldComeBefore( heap[ left ], heap[ i ] ) ) // First condition ensures no indexing out of bounds, second determines insertion place
	{
		smallest = left;
	}

	if ( right < size && shouldComeBefore( heap[ right ], heap[ smallest ] ) )
	{
		smallest = right;
	}

	if ( smallest != i ) // If not equal, swap then call this function recursively
	{
		Patient* tmp = heap[ i ];
		heap[ i ] = heap[ smallest ];
		heap[ smallest ] = tmp;
		rebuildHeap( smallest );
	}
}

int PQueueBH::getParentIndex( int i )
{
	return ( i - 1 ) / 2;
}

int PQueueBH::getLeftIndex( int i )
{
	return ( 2 * i + 1 );
}

int PQueueBH::getRightIndex( int i )
{
	return ( 2 * i + 2 );
}

// Helper function which runs function 500x