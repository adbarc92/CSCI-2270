#include <iostream>

struct Node
{
	int id = -1;
	Node* next = NULL;
	bool modified = false;
};

Node* createNode (int nodeID, Node* nextNode)
{
	Node* newNode = new Node;
	newNode->id = nodeID;
	newNode->next = nextNode;
	newNode->modified = false;
	return newNode;
}

Node* insertNode(Node* head, int newNodeID) {
	if (head == NULL) {
		Node* newNode = createNode(newNodeID, NULL);
		head = newNode;
	}
	else {
		Node* currentNode = head;
		while (currentNode->next != NULL) {
			currentNode = currentNode->next;
		}
		Node* newNode = createNode(newNodeID,NULL);
		currentNode->next = newNode;
	}
	return head;
}

void printList(Node* head) {
	if (head==NULL) {
		std::cout << "empty list" << std::endl;
	}
	else {
		Node* currentNode = head;
		while(currentNode != NULL) {
			std::cout << "Node ID: " << currentNode->id << std::endl;
			currentNode = currentNode->next;
		}
	}
}

Node* addEvenNodes (Node* head)
{
	if (head == NULL)
	{
		Node* newNode = createNode(0,NULL);
		head = newNode;
	}
	else
	{
		Node* currentNode = head;
		while (currentNode->next != NULL)
		{
			if (currentNode->id%2)
			{
				Node* newNode = createNode( (currentNode->id)+5, currentNode->next);
				currentNode->next = newNode->next;
			}
			
		}
	}
	return head;
}

int main()
{
	Node* head = NULL;
	insertNode(head, 15);
	insertNode(head, 60);
	insertNode(head, 10);
	insertNode(head, 18);

	printList(head);
}