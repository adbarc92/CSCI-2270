#include <iostream>

// Max Heap Implementation; only checks primary priority

struct priorityItem
{
	std::string itemName;
	int primaryPriority;
	int secondaryPriority;

};

class PriorityQueue
{
public:
	PriorityQueue();
	~PriorityQueue();
	bool enqueue( std::string, int, int );
	bool dequeue(); // Return false if empty
	std::string peek();
	void printPQ();
private:
	int lastIndex = 0; // If empty;
	int maxIndex = 10;
	priorityItem* pQueue[10];
};

PriorityQueue::PriorityQueue()
{
	for ( int i = 0; i < maxIndex; ++i ) // Initialize as nullptrs
	{
		pQueue[ i ] = nullptr;
	}
}

PriorityQueue::~PriorityQueue()
{
	for ( int i = 1; i < maxIndex; ++i )
	{
		delete pQueue[ i ];
	}
}