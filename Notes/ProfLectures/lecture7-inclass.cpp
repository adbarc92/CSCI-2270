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



int main() {
	int* arithPtr = new int;
	arithPtr++;
	arithPtr--;	//get arithPtr back to where it started before deleting it
	//arithPtr = NULL;	//you can also set it to NULL and then delete it.
	delete arithPtr;

	Node* head = NULL;
	head = insertNode(head,30);
	head = insertNode(head,10);
	head = insertNode(head,20);
	printList(head);


}