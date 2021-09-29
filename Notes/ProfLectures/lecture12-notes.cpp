#include <iostream>
using namespace std;

const int MAX_SIZE = 5;

class arrStack {
	public:
		arrStack();
		~arrStack();
		bool isEmpty();	//might want to make this private
		bool isFull();	//might want to make this private
						//you might think they aren't really needed -- they probably aren't.  the code they run is simple enough and could just be included in the functions that call them
		int peek();
		int pop();
		bool push(int);
	private:
		int stackOInts[MAX_SIZE];
		//if we wanted to be able resize this, what would we need to do?
			//dynamically allocate space for it
		int currentSize = 0;
};

arrStack::arrStack() {
	//nothing to see here
}
arrStack::~arrStack() {
	//nothing to see here
}

bool arrStack::isEmpty() {
	if (currentSize == 0) {
		return true;
	}
	else {
		return false;
	}
}

bool arrStack::isFull() {
	if (currentSize == MAX_SIZE) {
		return true;
	}
	else {
		return false;
	}
}

bool arrStack::push(int itemToAdd) {
	//if push is successful, return true
	//check if stack is full
	if (isFull()) {
		return false;
	}
	else {
		stackOInts[currentSize] = itemToAdd;
		currentSize+=1;
		return true;
	}
}

int arrStack::pop() {
	if (!isEmpty()) {
		int itemToReturn = stackOInts[currentSize-1];
		currentSize -= 1;
		return itemToReturn;
	}
	else {
		cout << "stack is empty" << endl;
		return -999999999;	//if your stack stores pointers, you can return nullptr here
	}
}

int arrStack::peek() {
	//return what's at the top of the stack
	if (!isEmpty()) {
		return stackOInts[currentSize-1];
	}
	else {
		cout << "stack is empty" << endl;
		return -999999999;
	}
}

int main () {
	arrStack matey;
	if (!matey.isEmpty()) {
		cout << "stack is empty" << endl;
	}
	if (matey.push(33)) {
		cout << "33 added to stack" << endl;
	}
	if (matey.push(44)) {
		cout << "44 added to stack" << endl;
	}
	if (matey.push(2)) {
		cout << "2 added to stack" << endl;
	}
	if (matey.push(19)) {
		cout << "19 added to stack" << endl;
	}
	if (matey.push(4)) {
		cout << "4 added to stack" << endl;
	}
	if (matey.push(13)) {
		cout << "13 added to stack" << endl;
	}
	else {
		cout << "13 not added to stack -- stack full" << endl;
	}
	
	cout << "what is at the top of the stack? " << matey.peek() << endl;

	matey.pop();
	matey.pop();
	cout << "what is at the top of the stack? " << matey.peek() << endl;
	matey.push(100);
	cout << "what is at the top of the stack? " << matey.peek() << endl;

	return 0;
}