#include <iostream>
struct Node
{
	int key;
	Node* next;
	Node* previous;
};

class doublyLL
{
private:
	Node* createNode(int key, Node* next, Node* previous);
	Node* head = nullptr;
	Node* tail = nullptr;
public:
	bool insertNodeAtEnd(int);
	bool deleteNode(int);
	void print_list();
	doublyLL(); // default constructor
	doublyLL(int); // overloaded constructor
	~doublyLL(); // destructor
};

Node* doublyLL::createNode(int key, Node* next, Node* previous)
{
	Node* newNode = new Node;
	newNode->key = key;
	newNode->next = next;
	newNode->previous = previous;
	return newNode;
}

bool doublyLL::insertNodeAtEnd(int key)
{
	if (head == nullptr)
	{
		head = createNode(key, nullptr, nullptr);
		tail = head;
	}
	else
	{
		Node* newNode = createNode(key, tail, nullptr);
		tail->next = newNode;
		tail = newNode;
	}
	return true;
}

bool doublyLL::deleteNode(int value)
{
	Node* currentNode = head;
	while (currentNode->key != value)
	{
		currentNode = currentNode->next;
	}
	if (currentNode == head)
	{
		/* code */
	}
	if (currentNode == tail) // If deleting tail
	{
		/* code */
	}
}

void doublyLL::print_list()
{

}