#include <iostream>

struct Node
{
	std::string message;
	int ID;
	Node* next;
	Node* previous;
};

Node* createNode(Node* nextNode, Node* previousNode, int newNodeID)
{
	Node* newNode = new Node;
	newNode->next = nextNode;
	newNode->ID = newNodeID;
	return newNode;
}

Node* insertNode(Node* head, Node* previous, int newNodeID)
{
	if (head == nullptr)
	{
		Node* newNode = createNode(head, nullptr, 1);
		head = newNode;
		return head;
	}
	else
	{
		int count = 0;
		while (head != previous)
		{
			count = count + 1;
		}
		Node* newNode = createNode(previous->next, previous, count);
		newNode->next = previous->next;
		previous->next = newNode;
		newNode->previous = previous;
	}
}