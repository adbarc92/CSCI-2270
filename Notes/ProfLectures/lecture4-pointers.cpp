#include <iostream>
using namespace std;

//pointer is a special kind of variable that contains a memory address

void passByVal(int a);
void passByRef(int &a);


int main() {
	int jenny = 5;
	int *jennyPtr;	//pointint to data type int
	jennyPtr = &jenny;


	int billy = 2;
	int jimmy = 3;

	cout << "what's jenny? " << jenny << endl;
	cout << "what's reference to jenny (&):" << &jenny << endl;
	cout << "what's jennyptr? " << jennyPtr << endl;
	cout << "what's stored at jennyptr? " << *jennyPtr << endl;

	//so what's the difference between references and pointers?
	//pointers can be reassigned, references cannot

	cout << "billy: " << billy << endl;
	cout << "jimmy: " << jimmy << endl;

	//can i move the kenny reference to the jimmy reference?
	//&jenny = &billy; nope

	//can i set the jenny pointer to billy's reference?
	jennyPtr = &billy;
	//now, what's in jennyPtr when we dereference it?
	cout << "jennyPtr is now " << jennyPtr << endl;
	cout << "dereferencing jennyPtr: " << *jennyPtr << endl;


	passByVal(jenny);
	cout << "what's jenny after pass by val? " <<  jenny << endl;
	//passByRef(jenny);
	//cout << "what's jenny after pass by ref? " << jenny << endl; 

	passByVal(jimmy);	//shouldn't change jimmy
	passByRef(billy);	//should change billy
	cout << "jimmy is " << jimmy << endl;
	cout << "billy is " << billy << endl;
	cout << "jennyPtr is now " << jennyPtr << endl;
	cout << "dereferencing jennyPtr: " << *jennyPtr << endl;
	cout << "jenny is a different variable" << jenny << endl;
}




void passByVal(int a) {
	++a;
}

void passByRef(int &a) {
	++a;	//this will increase a by one
}