#include <iostream>

struct Node
{
	int id = -1;
	Node* next = nullptr;
};

class singlyLL
{
public: 
	singlyLL ();
	singlyLL (int); // Overloaded constructor
	~singlyLL ();
	bool insertNodeAtEnd (int);
	bool deleteNode (int);
	void printList ();

private:
	Node* createNode(int,Node*);
	Node* head = nullptr;
	void deleteList();
};

singlyLL::singlyLL ()
{

}

singlyLL::singlyLL(int)
{

}

singlyLL::~singlyLL()
{
	deleteList();
}

void singlyLL::deleteList()
{
	Node* currentNode = head;
	Node* tmpNode;

	while (currentNode != nullptr)
	{
		tmpNode = currentNode->next;
		std::cout << "Deleting node " << currentNode->id << std::endl;
		delete currentNode; // Deletes what currentNode is presently pointing at
		currentNode = tmpNode; // Moves currentNode to point at the temporary node
	}
}

int main()
{

}

