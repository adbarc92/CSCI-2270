#include <iostream>

struct Node
{
	std::string nodeName;
	Node* next;
	std::string message;

	Node(){};
	Node( std::string initName, Node* initNext, std::string initMessage )
	{
		nodeName = initName;
		next = initNext;
		message = initMessage;
	}
};

Node* addNode( Node* head, Node* previous, std::string nodeName )
{
	if (head == nullptr)
	{
		head = new Node;
		head->nodeName = nodeName;
		head->next = nullptr;
		return head;
	}
	
	else
	{
		if (previous == nullptr)
		{
			/* code */
		}
		Node* newNode = new Node;
		newNode->next = previous->next;
		newNode->nodeName = nodeName;

	}

}