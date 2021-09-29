#pragma once

#include "Entry.hpp"

struct PQueueLLNode;

class PQueueLL
{
public:
	PQueueLL();
	~PQueueLL();

	void enqueue(Entry* e);
	Entry* dequeue();
private:
	PQueueLLNode* root;
};
