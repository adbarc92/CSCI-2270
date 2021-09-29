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

Node* insertEvenNode(Node* head, int newNodeID) {
	if (head == NULL) {
		Node* newNode = createNode(newNodeID, NULL);
		head = newNode;
	}
	else {
		Node* currentNode = head;
		while (currentNode->next != NULL) {
			if (currentNode->id%2)
			{
				Node* newNode = createNode(newNodeID,NULL);
				return newNode;
			}
			currentNode = currentNode->next;
		}
	}
	return head;
}

Node* deleteNode(Node* head, int nodeID) {
	//find the node
	bool nodeFound = false;
	//first check if head is null
	if (head == NULL) {
		std::cout << "empty list, nothing to delete" << std::endl;
		return NULL;
	}
	else {
		//first check the head
		if (head->id == nodeID) {
			//need to delete the head. what becomes the new head?
				//whatever is next
			Node* nextNode = head->next;
			delete head;
			head = nextNode;
			nodeFound = true;
			std::cout << "node " << nodeID << " deleted" << std::endl;
		}
		else if (head->next != NULL && head->next->id == nodeID) {
			//delete the second node
			Node* newNextNode = head->next->next;
			delete head->next;
			head->next = newNextNode;
			nodeFound = true;
			std::cout << "node " << nodeID << " deleted" << std::endl;
		}
		else {
			Node* currentNode = head->next;
			while (currentNode != NULL && currentNode->next != NULL && !nodeFound) {
				/*currentNode != NULL handles the case where there is only one 
				element in the list (the head) and it is not nodeID*/
				if (currentNode->next->id == nodeID) {
					Node* newNextNode = currentNode->next->next;
					delete currentNode->next;
					currentNode->next = newNextNode;
					nodeFound = true;
					std::cout << "node " << nodeID << " deleted" << std::endl;
				}
				else {
					currentNode = currentNode->next;
				}
			}
			if (!nodeFound) {
				std::cout << "node " << nodeID << " not found, nothing deleted" << std::endl;
			}
		}
		return head;
	}
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

// If even, insert node

int main ()
{
	Node* head = NULL;
	for (int i = 0; i < 10; ++i)
	{
		head = insertNode (head,i+1);
	}
	insertEvenNode(head,6);
	printList(head);
}