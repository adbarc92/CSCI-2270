#include <iostream>
#include <time.h> // Timing Library - clock for measuring 

struct priorityItem
{
	std::string itemName;
	int primaryPriority; // Time to delivery (lowest)
	int secondaryPriority; // Treatment time (lowest)
};

class PriorityQueue
{
	public:
		PriorityQueue();
		~PriorityQueue();
		bool enqueue( std::string, int, int );
		bool dequeue();
		std::string peek();
		void printPQ();
	private:
		int lastIndex = 0;
		int maxIndex = 10;
		priorityItem* pQueue[ 10 ];
};

PriorityQueue::PriorityQueue(){
	for ( int i = 0; i <= maxIndex; i++ )
	{
	pQueue[ i ] = nullptr;
	}
}

PriorityQueue::~PriorityQueue(){
	for (int i = 0; i < lastIndex; ++i)
	{
		delete pQueue[i];
	}
}

bool PriorityQueue::enqueue( std::string thingName, int primP, int secP )
{
	// if you wanted to dynamically resize the heap
		// check if queue is full
	if ( lastIndex < maxIndex )
	{
		priorityItem* itemToAdd = new priorityItem;
		itemToAdd->itemName = thingName;
		itemToAdd->primaryPriority = primP;
		itemToAdd->secondaryPriority = secP;
		lastIndex++;
		// New thing at last index;
		pQueue[ lastIndex ];
		// Reheap up
		int currentIndex = lastIndex;
		bool itemSwapped = true;
		while ( currentIndex > 1 && itemSwapped ) // While not at root and item just swapped
		{
			// Compare thing at current index to parent
			// This only checks primary priority
			if ( pQueue[ currentIndex ]->primaryPriority > pQueue[ currentIndex/2 ]->primaryPriority )
			{
				// If true, swap;
				priorityItem* temp = pQueue[ currentIndex/2 ];
				pQueue[ currentIndex/2 ] = pQueue[ currentIndex ];
				pQueue[ currentIndex ] = temp;
				currentIndex = currentIndex/2;
			}
			else
			{
				itemSwapped = false; // Binary heap is partially ordered
			}
		}
		return true;
	}
	else
	{
		std::cout << "Queue is full" << std::endl;
		return false;
	}
}

std::string PriorityQueue::peek()
{
	if ( lastIndex != 0 )
	{
		return pQueue[ 1 ]->itemName;
	}
	else
	{
		std::cout << "Priority Queue Empty" << std::endl;
		return "N/A";
	}
}

bool PriorityQueue::dequeue()
{
	if ( lastIndex > 0 )
	{
		delete pQueue[ 1 ];
		// Move last index to top
		pQueue[ 1 ] = pQueue[ lastIndex ];
		// Check if priorityQueue is empty
		if ( lastIndex == 1 )
		{
			lastIndex = 0;
			pQueue[ 1 ] = nullptr;
			// Done
		}
		else
		{
			// Set item 1 to thing at end
			pQueue[ 1 ] = pQueue[ lastIndex ];
			// Set last thing to nullptr
			pQueue[ lastIndex ] = nullptr;
			// Decrement lastIndex
			lastIndex--;
			//Reheap down
			int currentIndex = 1;
			int leftChild, rightChild, largerChild;
			bool itemSwapped = true;
			while ( currentIndex < maxIndex && itemSwapped )
			{
				// Root is 1
				leftChild = currentIndex * 2;
				rightChild = currentIndex * 2 + 1;
				// Check if you're out of bounds
				if ( leftChild > lastIndex ) // Compare because those
				{
					// No children, so stop
					itemSwapped = false;
				}
				else
				{
					if ( rightChild > lastIndex )
					{
						largerChild = leftChild;
					}
					else
					{
						// Need to compare the children
						largerChild = (pQueue[ leftChild ]->primaryPriority > pQueue[ rightChild ]->primaryPriority ) ? leftChild : rightChild;
					}
				}
				if ( pQueue[ currentIndex ]->primaryPriority < pQueue[ largerChild ]->primaryPriority )
				{
					priorityItem* temp = pQueue[ largerChild ];
					pQueue[ largerChild ] = pQueue[ currentIndex ];
					pQueue[ currentIndex ] = temp;
					// Move current index to index of larger child
					currentIndex = largerChild;
				}
				else
				{
					itemSwapped = false;
				}
			}
		}
		return true;
	}
	else
	{
		std::cout << "Priority Queue is empty, nothing to dequeue" << std::endl;
		return false;
	}
}

// Default implementation of STL priorityQueue is MaxHeap
// Array implementation
// Binary Heap implementation
// Vector implementation is extra credit
// Dynamically-resized heap is an option