#ifndef doublyLL_H
#define doublyLL_H

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

#endif