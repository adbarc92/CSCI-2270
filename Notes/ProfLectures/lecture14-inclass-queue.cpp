#include <iostream>
using namespace std;

struct Node {
	int id = -1;
	Node* prev = nullptr;
	Node* next = nullptr;
};

class llQueue {
	private:
		Node* createNode(int, Node*, Node*);
		bool isEmpty();
		void deleteQueue();
		Node* head = nullptr;
		Node* tail = nullptr;
	public:
		llQueue();
		llQueue(int);
		~llQueue();
		bool enqueue(int);
		bool dequeue(int&);
		bool peek(int&);

};


//dequeue
//where does dequeue happen?
	//head
bool llQueue::dequeue(int& itemToGet) {
	if (!isEmpty()) {
		//off with its head!
		//handle case where we're dequeing the last thing in the queue
		itemToGet = head->id;
		if (head->next == nullptr) {
			delete head;
			head = tail = nullptr;
		}
		else {
			Node* tempNode = head;
			head = head->next;
			head->prev = nullptr;
			delete tempNode;
		}
		return true;
	}
	else {
		cout << "empty list" << endl;
		return false;
	}
}


















