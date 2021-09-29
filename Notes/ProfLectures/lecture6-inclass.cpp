//lecture 6

#include <iostream>
using namespace std;

void leaky(double* dblPtr) {
	double* leakyCopy = dblPtr;
	*dblPtr = (*dblPtr)*(*dblPtr);
}
//leakyCopy leaks memory



int main() {
	int *anIntPointer = NULL;
	anIntPointer = new int;
	*anIntPointer = 500;
	cout << "anIntPointer is storing: " << *anIntPointer << endl;

	delete anIntPointer;

	/* INSTRUCTOR'S NOTE */
	/* The following code is for illustration purposes only. Don't do this sort of stuff or you might tear a hole in the fabric of reality. Or just segfault a lot.  You have been warned. */
	int* intPtr = new int;
	*intPtr = 17;

	cout << "intPtrReference: " << intPtr << endl;
	cout << (*intPtr)++ << endl;
	cout << "intPtrReference: " << intPtr << endl;
	cout << "what's in intPtr? " << *intPtr << endl;;

	double* dblPtr = new double(55.248575);
	cout << "doubleptr reference: " << dblPtr << endl;
	cout << "doubleptr value: " << *dblPtr << endl;

	double* secDblPtr = dblPtr;
	cout << "secDoubleptr reference: " << secDblPtr << endl;
	cout << "secDoubleptr value: " << *secDblPtr << endl;

	cout << "incrementing *dblPtr" << endl;
	(*dblPtr)++;
	cout << "doubleptr reference: " << dblPtr << endl;
	cout << "doubleptr value: " << *dblPtr << endl;

	cout << "secDoubleptr reference: " << secDblPtr << endl;
	cout << "secDoubleptr value: " << *secDblPtr << endl;

	dblPtr++;	//if you try to delete after this, you'll get a runtime error. You have to get dblPtr back to its original memory address before trying to delete it 
	
	cout << "doubleptr reference: " << dblPtr << endl;
	cout << "doubleptr value: " << *dblPtr << endl;
	
	cout << "increased dblPtr reference: " << dblPtr << endl;
	cout << "secDoubleptr reference: " << secDblPtr << endl;
	cout << "secDoubleptr value: " << *secDblPtr << endl;

	cout << "doubleptr reference: " << dblPtr << endl;
	cout << "doubleptr value: " << *dblPtr << endl;

}