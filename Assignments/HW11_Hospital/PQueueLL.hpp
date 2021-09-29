#pragma once

#include "PQueueHelper.hpp"

struct PQueueLLNode;

class PQueueLL
{
public:
	PQueueLL();
	~PQueueLL();
	Patient* dequeue();
	void enqueue( Patient* p );
private:
	PQueueLLNode* head;
};