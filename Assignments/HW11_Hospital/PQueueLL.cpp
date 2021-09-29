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