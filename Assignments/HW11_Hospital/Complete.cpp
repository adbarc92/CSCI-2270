#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <functional>
#include <queue>
#include <chrono>

#include "PQueueHelper.hpp"
#include "PQueueBH.hpp"
#include "PQueueLL.hpp"

//-----------------------------------------------------------------------------
//=================================PQueueLL====================================
//-----------------------------------------------------------------------------

#include "PQueueLL.hpp"

#include <iostream>
#include <stdexcept> // What is this?

struct PQueueLLNode
{
	PQueueLLNode* next;
	Patient* key;
};

PQueueLL::PQueueLL()
{
	head = nullptr;
}

PQueueLL::~PQueueLL(){
	
	PQueueLLNode* currentNode = head;
	while( currentNode != nullptr )
	{
		PQueueLLNode* tmpNode = currentNode->next;
		delete currentNode;
		currentNode = tmpNode;
	}
}

void PQueueLL::enqueue( Patient* p )
{
	PQueueLLNode* newNode = new PQueueLLNode;
	newNode->key = p;
	newNode->next = nullptr;

	if ( head == nullptr )
	{
		head = newNode;
		return;
	}

	else if ( shouldComeBefore( p, head->key ) )
	{
		newNode->next = head;
		head = newNode;
		return;
	}

	else if ( head->next == nullptr )
	{
		head->next = newNode;
		return;
	}

	PQueueLLNode* prevNode = head;
	for ( PQueueLLNode* n = head; n != nullptr; n = n->next )
	{
		if ( shouldComeBefore( p, n->key ) )
		{
			newNode->next = n;
			prevNode->next = newNode;
			break;
		}
		else if ( n->next == nullptr )
		{
			n->next = newNode;
			break;
		}
		prevNode = n;
	}
}

Patient* PQueueLL::dequeue()
{
	if ( head == nullptr )
	{
		throw -1;
	}

	Patient* p = head->key;
	PQueueLLNode* tmpNode = head->next;
	delete head;
	head = tmpNode;
	return p;
}

//-----------------------------------------------------------------------------
//=================================PQueueBH====================================
//-----------------------------------------------------------------------------

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

//-----------------------------------------------------------------------------
//===================================Driver====================================
//-----------------------------------------------------------------------------

int read_csv( const std::string& fileName, Patient patients[] )
{
	int i = 0;
	std::string line = "";
	std::fstream csv;

	csv.open( fileName );
	if ( !csv )
	{
		std::cout << "Error reading file: " << fileName << std::endl;
	}

	getline( csv, line );
	while ( getline( csv, line ) )
	{
		Patient& p = patients[ i ];
		std::string priority, treatment;
		std::stringstream ss( line );
		getline( ss, p.name, ',' );
		getline( ss, priority, ',' );
		getline( ss, treatment, ',' );
		p.priority = stoi( priority );
		p.treatment = stoi( treatment );
		i++;
	}

	return i;
}

void create_csv( std::vector< float > durationsBH, std::vector< float > durationsLL, std::vector< float > durationsSTD )
{
	std::ofstream myFile( "runtime.csv" );

	myFile << "BinaryHeap,LinkedList,PriorityQueue\n"; // Headers

	for (int i = 0; i < 500; ++i)
	{
		myFile << std::to_string(durationsBH[ i ]) + ",";
		myFile << std::to_string(durationsLL[ i ]) + ",";
		myFile << std::to_string(durationsSTD[ i ]);
		myFile << "\n";
	}

	myFile.close();
}

float timeSTD( Patient patients[] )
{
	auto startSTD = std::chrono::system_clock::now();
	
	std::priority_queue< Patient*, std::vector< Patient* >, ComparePatientPointers > pq; // Builds priority queue: data type, data structure, comparison method

	for (int i = 0; i < 880; ++i) // Enqueue - Remove hardcoding, if time allows
	{
		pq.push( &patients[ i ] );
	}

	for (int i = 0; i < int( pq.size() ); ++i) // Dequeue
	{
		pq.top();
		pq.pop();
	}

	auto endSTD = std::chrono::system_clock::now();
	auto timeElapsedSTD = std::chrono::duration< float >( endSTD - startSTD );

	return timeElapsedSTD.count();
}

float timeLL( Patient patients[] )
{
	auto startLL = std::chrono::system_clock::now();
	
	PQueueLL pq;
	for (int i = 0; i < 880; ++i) // Enqueue
	{
		pq.enqueue( &patients[ i ] );
	}

	for (int i = 0; i < 880; ++i) // Dequeue
	{
		pq.dequeue();
	}

	auto endLL = std::chrono::system_clock::now();
	
	auto timeElapsedLL = std::chrono::duration< float >( endLL - startLL );

	return timeElapsedLL.count();
}

float timeBH( Patient patients[] )
{
	auto startBH = std::chrono::system_clock::now();

	PQueueBH pq;
	
	for (int i = 0; i < 880; ++i) // Enqueue
	{
		pq.enqueue( &patients[ i ] );
	}

	for (int i = 0; i < 880; ++i)
	{
		pq.dequeue();
	}

	auto endBH = std::chrono::system_clock::now();
	
	auto timeElapsedLL = std::chrono::duration< float >( endBH - startBH );

	return timeElapsedLL.count();
}

int main()
{
	Patient patients[ 880 ];
	std::string fileName = "patientData2270.csv";
	read_csv( fileName, patients );
	
	std::vector< float > durationsBH;
	std::vector< float > durationsLL;
	std::vector< float > durationsSTD;

	for (int i = 0; i < 500; ++i)
	{
		float duration = timeBH( patients );
		durationsBH.push_back( duration );
	}

	for (int i = 0; i < 500; ++i)
	{
		float duration = timeLL( patients );
		durationsLL.push_back( duration );
	}

	for (int i = 0; i < 500; ++i)
	{
		float duration = timeSTD( patients );
		durationsSTD.push_back( duration );
	}

	create_csv( durationsBH, durationsLL, durationsSTD );
}