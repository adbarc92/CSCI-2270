#include <iostream>
using namespace std;

const int MAX_SIZE=5;

class arrCircQueue {
	public:
		arrCircQueue();
		~arrCircQueue();
		bool enqueue(int);
		bool dequeue(int&);
		bool peek (int&);
	private:
		bool isFull();
		bool isEmpty();
		int head = -1;
		int tail = -1;
		int arrQueue[MAX_SIZE];
};

arrCircQueue::arrCircQueue() {

}

arrCircQueue::~arrCircQueue() {

}

bool arrCircQueue::isFull() {
	int tempHead = head;
	if (head == 0) {
		tempHead = MAX_SIZE;
	}
	if (tempHead - tail == 1) {
		return true;
	}
	else {
		return false;
	}
}

bool arrCircQueue::isEmpty() {
	if (head == -1 && tail == -1) {
		return true;
	}
	else {
		return false;
	}
}

bool arrCircQueue::enqueue(int itemToAdd) {
	if (!isFull()) {
		//add item
		int tempTail = tail+1;
		if (tempTail == MAX_SIZE) {
			tempTail = 0;
		}
		tail = tempTail;
		arrQueue[tail] = itemToAdd;
		if (head == -1) {
			head = 0;
		}
		cout << "item " << itemToAdd << " added to queue" << endl;
		return true;
	}
	else {
		cout << "queue full, item " << itemToAdd << " not added to queue" << endl;
		return false;
	}
}

bool arrCircQueue::dequeue(int& itemToGet) {
	if (isEmpty()) {
		cout << "queue empty, nothing to dequeue" << endl;
		return false;
	}
	else {
		//remove at head
		itemToGet = arrQueue[head];
		//check if list is now empty
		if (head==tail) {
			//nothing left in the queue
			head = tail = -1;
		}
		else {
			head+=1;
			if (head == MAX_SIZE) {
				head = 0;
			}
		}
		return true;
	}
}


int main() {
	arrCircQueue pirateQ;
	pirateQ.enqueue(16);
	pirateQ.enqueue(19);

	int topOQueue;

	if (pirateQ.dequeue(topOQueue)) {
		cout << "dequeued " << topOQueue << endl;
	}
}