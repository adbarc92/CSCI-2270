#include <iostream>
using namespace std;

struct Node {
	int id = -1;
	Node* next = nullptr;
};

class llStack {
	private:
		Node* head = nullptr;
		void deleteStack();
		Node* createNode(int, Node*);
		bool isEmpty();
	public:
		llStack();
		llStack(int);
		~llStack();
		bool push(int);
		bool pop(int&);
		bool peek(int&);
};

llStack::llStack() {

}

llStack::llStack(int itemToAdd) {
	Node* newNode = createNode(itemToAdd, nullptr);
	head = newNode;
}

Node* llStack::createNode(int nodeID, Node* nodeNext) {
	Node* newNode = new Node;
	newNode->id = nodeID;
	newNode->next = nodeNext;

	return newNode;
}

llStack::~llStack() {
	deleteStack();
}

void llStack::deleteStack() {
	//for you to write
}

bool llStack::push(int itemToAdd) {
	//new nodes in the stack go where?
		//the head
	Node* newNode = createNode(itemToAdd,head);
	head = newNode;
	return true;
}

bool llStack::pop(int& itemToGet) {
	//where do we always always always pop from?
		//the head
	if (!isEmpty()) {
		itemToGet = head->id;
		//remove head
		Node* tempNode = head;
		//what becomes the new head?
		head = head->next;
		delete tempNode;

		return true;
	}
	else {
		cout << "stack is empty" << endl;
		return false;
	}
}

bool llStack::isEmpty() {
	if (head == nullptr) {
		return true;
	}
	else {
		return false;
	}
}

int main() {
	llStack stackOne(15);
	stackOne.push(33);

	int nodeIDToGet;
	if (stackOne.pop(nodeIDToGet)) {
		cout << "Node with id " << nodeIDToGet << " just removed from stack" << endl;
	}
	if (stackOne.pop(nodeIDToGet)) {
		cout << "Node with id " << nodeIDToGet << " just removed from stack" << endl;
	}
	if (stackOne.pop(nodeIDToGet)) {
		cout << "Node with id " << nodeIDToGet << " just removed from stack" << endl;
	}
}






