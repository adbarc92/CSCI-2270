#include "PQueueLL.hpp"

#include <stdexcept>
#include <iostream>

using namespace std;

struct PQueueLLNode
{
	PQueueLLNode* next;
	Entry* payload;
};

PQueueLL::PQueueLL()
{
	root = nullptr;
}
PQueueLL::~PQueueLL()
{
	PQueueLLNode* node = root;
	while (node != nullptr)
	{
		PQueueLLNode* next = node->next;
		delete node;
		node = next;
	}
}

void PQueueLL::enqueue(Entry* e)
{
	PQueueLLNode* new_node = new PQueueLLNode;
	new_node->payload = e;
	new_node->next = nullptr;

	if (root == nullptr)
	{
		root = new_node;
		return;
	}
	else if (should_come_before(e, root->payload))
	{
		new_node->next = root;
		root = new_node;
		return;
	}
	else if (root->next == nullptr)
	{
		root->next = new_node;
		return;
	}
	
	PQueueLLNode* prev = root;
	for (PQueueLLNode* n = root; n != nullptr; n = n->next)
	{
		if (should_come_before(e, n->payload))
		{
			new_node->next = n;
			prev->next = new_node;
			break;
		}
		else if (n->next == nullptr)
		{
			n->next = new_node;
			break;
		}
		prev = n;
	}
}

Entry* PQueueLL::dequeue()
{
	if (root == nullptr)
	{
		throw std::runtime_error("cannot dequeue an empty list");
	}

	Entry* ret = root->payload;
	PQueueLLNode* tmp = root->next;
	delete root;
	root = tmp;
	return ret;
}