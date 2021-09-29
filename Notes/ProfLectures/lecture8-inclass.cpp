#include <iostream>
using namespace std;

struct Node {
	int id=-1;
	Node* next = NULL;
};

Node* createNode(int nodeID, Node* nextNode) {
	Node* newNode = new Node;
	newNode->id = nodeID;
	newNode->next = nextNode;
	return newNode;
}


//insertNode -- inserts at end, returns head of list
Node* insertNode(Node* head, int newNodeID) {
	//first thing: check if head is null
	if (head == NULL) {
		Node* newNode = createNode(newNodeID, NULL);
		head = newNode;
	}
	else {
		//where does the new node go? at the end
		Node* currentNode = head;
		//traverse to the end of the list
		while (currentNode->next != NULL) {
			currentNode = currentNode->next;
		}
		Node* newNode = createNode(newNodeID,NULL);
		currentNode->next = newNode;
	}
	return head;
}//worst case: O(n)

void printList(Node* head) {
	if (head==NULL) {
		cout << "empty list" << endl;
	}
	else {
		Node* currentNode = head;
		while(currentNode != NULL) {
			cout << "Node ID: " << currentNode->id << endl;
			currentNode = currentNode->next;
		}
	}
}

Node* deleteNode(Node* head, int nodeID) {
	//find the node
	bool nodeFound = false;
	//first check if head is null
	if (head == NULL) {
		cout << "empty list, nothing to delete" << endl;
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
			cout << "node " << nodeID << " deleted" << endl;
		}
		else if (head->next != NULL && head->next->id == nodeID) {
			//delete the second node
			Node* newNextNode = head->next->next;
			delete head->next;
			head->next = newNextNode;
			nodeFound = true;
			cout << "node " << nodeID << " deleted" << endl;
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
					cout << "node " << nodeID << " deleted" << endl;
				}
				else {
					currentNode = currentNode->next;
				}
			}
			if (!nodeFound) {
				cout << "node " << nodeID << " not found, nothing deleted" << endl;
			}
		}
		return head;
	}
}

int main() {
	Node* head = NULL;
	head = insertNode(head,30);
	head = insertNode(head,10);
	head = insertNode(head,20);
	printList(head);

	head = deleteNode(head,30);
	printList(head);
	head = deleteNode(head,20);
	printList(head);
	head = deleteNode(head,5);
	head = deleteNode(head,10);
	printList(head);

}