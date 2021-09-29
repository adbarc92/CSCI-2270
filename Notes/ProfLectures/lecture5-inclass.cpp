#include <iostream>

using namespace std;


void passByPointer(int *ptr) {
	//*ptr = *ptr + 1;	//this works
	//++*ptr;	//this works
	//*ptr++;	//this doesn't work as intended -- order of operations
	(*ptr)++; //this works because we used parentheses
}

int* multiplyArraySize(int p[], int length, int multiplier) {
	int *newArray = new int[length*multiplier];
	for (int i=0; i<length; i++) {
		newArray[i] = p[i];
	}
	delete [] p;
	//if you don't use the brackets you're only going to delete the first element in the array and you're going to have a bad time
	return newArray;
}


int main() {
	//can i do this?
	int x=10;
	while (x-->0) {	//as x goes to zero?  nope!
		cout << "x: " << x << endl;
	}
	//you can do this! why?  order of operations! -- first, then >

	//stack: managed by the operating system as the program runs. contains the local variables that are statically declared, e.g., int myInt = 9;
	//stack space is limited. when a variable isn't in scope, the memory is freed.

	//heap: large pool of free memory, larger than the stack
	//variables that are created dynamically during runtime are stored on the heap
	//pointers are used to access these variables
	//memory is managed *by the programmer*!
	//allocated memory stays allocated until it is deallocated
	//new allocates memory, delete deallocates memory

	int normalInt;  //statically declared, so it's in the stack
	normalInt = 9;
	normalInt = 8;
	int *intPtr = new int; // dynamically declared, so it's in the heap
	delete intPtr; //free up memory so the memory can be allocated to something else
	//BUT if you go back to that spot in memory, there might be something familiar there. be careful!
	*intPtr = 0;
	cout << "what is stored in *intPtr? " << *intPtr << endl;
	cout << "what is stored in intPtr? " << intPtr << endl;
	passByPointer(intPtr);
	cout << "what is stored in *intPtr? " << *intPtr << endl;
	cout << "what is stored in intPtr? " << intPtr << endl;

	int *myArray = new int[200];
	//using a pointer here allows us to delete this array should the need arise.
	int staticArray[200]; //we can't delete this array since it was statically declared
	for (int i=0; i<200; i++) {
		myArray[i] = i+i;
	}
	cout << "reference of myArray: " << myArray << endl;
	cout << "reference of staticArray: " << staticArray << endl;

	int *aNewArray = multiplyArraySize(myArray,200,3);
	for (int i=0; i<600; i++) {
		cout << "index " << i <<": " << aNewArray[i] << endl;
	}
}