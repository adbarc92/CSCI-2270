// lecture 9-10, 05/07Feb2018

#include <iostream>
using namespace std;


struct Node {
			int id=-1;
			Node* next = nullptr;
		};

class singlyLL {
	private:
		Node* createNode(int,Node*);
		Node* head = nullptr;
		void deleteList();

	public:
		singlyLL();
		singlyLL(int);	//overloaded constructor
		~singlyLL();
		bool insertNodeAtEnd(int);
		bool deleteNode(int);
		void printList();
};

//default constructor
singlyLL::singlyLL() {
	//ze constructor does nothing
}

//overloaded constructor
singlyLL::singlyLL(int nodeID) {
	//set head with the nodeID
	head = createNode(nodeID,nullptr);
}

singlyLL::~singlyLL() {
	deleteList();
}

Node* singlyLL::createNode(int nodeID, Node* nextNode) {
	Node* newNode = new Node;
	newNode->id = nodeID;
	newNode->next = nextNode;
	return newNode;
}

bool singlyLL::insertNodeAtEnd(int nodeID) {
	Node* newNode = createNode(nodeID, nullptr);
	if (head == nullptr) {
		head = newNode;
	}
	else {
		//where does the new node go? at the end
		Node* currentNode = head;
		//traverse to the end of the list
		while (currentNode->next != nullptr) {
			currentNode = currentNode->next;
		}
		currentNode->next = newNode;
	}
	//shouldn't be a case where this doesn't return true
	return true;
}

void singlyLL::printList() {
	if (head == nullptr) {
		cout << "empty list" << endl;
	}
	else {
		Node* currentNode = head;
		while (currentNode != nullptr) {
			cout << "Node ID: " << currentNode->id << endl;
			currentNode = currentNode->next;
		}
	}
}

void singlyLL::deleteList() {
	//start at the head
	Node* currentNode = head;
	Node* tmpNode;
	while (currentNode != nullptr) {
		tmpNode = currentNode->next;
		cout << "deleting node " << currentNode->id << endl;
		delete currentNode;
		currentNode = tmpNode;
	}
}

int main() {
	singlyLL* thirdList = new singlyLL(99);	//dynamically create a pointer to an object
	thirdList->printList();
	//(*thirdList).printList();	//this results in the same outcome as above
	delete thirdList;	//since thirdList is on the heap, we must delete it directly. delete invokes the destructor.

	singlyLL llCoolList;
	llCoolList.printList();
	
	llCoolList.insertNodeAtEnd(15);
	llCoolList.insertNodeAtEnd(30);
	llCoolList.insertNodeAtEnd(5);

	singlyLL secondList(37);
	secondList.insertNodeAtEnd(44);

	cout << "printing first list" << endl;
	llCoolList.printList();

	cout << "printing second list" << endl;
	secondList.printList();


	return 0;
}