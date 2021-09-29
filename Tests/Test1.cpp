#include <iostream>

// -----------------------------------------------------------------
// Multiple Choice
// Score: 18.80/25.00
// -----------------------------------------------------------------

// Question 1: What is the output of the following code fragment? 

// int v1=2, v2=-1, *p1, *p2; 
// p1 = & v1; 
// p2= & v2; 
// p2=p1; 
// cout << *p2 << endl;

	// Answers:
		// a. 1
		// b. -2
		// c. -1
		// d. 2 <-- Correct

// Question 2: What are the valid indexes for the array shown below? 

// int myArray[25];
	
	// Answers:
		// a. 0-24 <-- Correct
		// b. 1-25
		// c. 1-24
		// d. 0-25

// Question 3: If you write a function that should use call-by-reference, but forget to include the ampersand in your function definition...
	// Answers: 
		// a. The program will run as expected.
		// b. The program will run but the results may be incorrect. <~ Correct
		// c. The program will not run without a run-time error.
		// d. The program will not compile.
		// e. The program will not link. <--
	// Work:
		// int passByRef(int a, int b)
		// {
		// 	std::cout << a << " " << b << " " << std::endl;
		// 	a++;
		// 	b++;

		// 	int c;
		// 	c = a + b;
		// 	std::cout << a << " " << b << " " <<  c << " " << std::endl;
		// 	return c;
		// }

		// int main()
		// {
		// 	int a = 1;
		// 	int b = 2;

		// 	int& ax = a;
		// 	int& bx = b;
			
		// 	passByRef(ax,bx);
		// 	std::cout << a << " " << b << " " << std::endl;

		// 	std::cout << a << b << std::endl;
		// }

// Question 4: Consider the following linked list - 

	// 4/Head <-> 3 <-> 1 <-> 2 <-> 5/Tail

	// The following code runs:

	// temp = tail->prev->prev; 
	// temp->prev->next = temp->next;
	// temp->next->prev = temp->prev; 
	// temp->next  = NULL;
	// temp->prev = NULL;

	// What is the node order when traversing the list from tail to head?  Write each number separated by a single space.

	// Answers: 
		// a. 5 2 1 3 4
		// b. 5 3 1 2 4
		// c. 5 2 3 1 4
		// d. 5 2 3 4 <-- Correct

// Question 5: 
	// Stacks - What are the contents of the stack after running the following code? The stack is implemented with an array. Enter -1 for any spaces in the array that aren't used.

	// push(8)
	// push(2)
	// pop()
	// push(7)
	// pop()
	// push(31)

	// Answer (Fill-in-the-Blank): stack[0] = 8, stack[1] = 31, empty <- Correct

	// Queues: What are the contents of the queue after running the following code? The queue is implemented with an array. Enter -1 for any spaces in the array that aren't used.

	// Enqueue(8)
	// Enqueue(2)
	// Dequeue()
	// Enqueue(7)
	// Dequeue()
	// Enqueue(31)

	// Answer (Fill-in-the-Blank): [2] = 31, empty <~ Incorrect

// -----------------------------------------------------------------
// Programming
// Score: 70.00/70.00
// -----------------------------------------------------------------

// Question 1: Write a function that takes an array, the size of the array, and a search integer as arguments and returns a pointer to a new array that contains only the numbers from the input array that are greater than the search integer. You need to use dynamic memory allocation to create the new array.

// int* makeNewArray( int inputArray[], int arraySize, int compareNum)
// {
// 	int newArraySize = 0;

// 	for (int i = 0; i < arraySize; ++i) // Find number of elements matching criteria
// 	{
// 		if (inputArray[i] > compareNum)
// 		{
// 			newArraySize++;
// 		}
// 		else
// 			continue;
// 	}

// 	int* newArray = new int[newArraySize]; // Create dynamically-allocated array
// 	int index = 0;

// 	for (int i = 0; i < arraySize; ++i)
// 	{
// 		if (inputArray[i] > compareNum)
// 		{
// 			newArray[index] = inputArray[i];
// 			index++;
// 		}
// 		else
// 			continue;
// 	}

// 	return newArray;
// }

// int main()
// {
// 	int A[4] = {100,200,300,400};
// 	int *r = makeNewArray(A,4,200);
	
// 	for(int i=0;i<2;i++)
// 	{
// 		std::cout<<r[i]<<" ";
// 	}
// }

//-----------------------------------------------------------------
// Author's Solution

// int *makeNewArray(int inputArray[], int arraySize, int compareNum) {
//     int newSize = 1;
//     for (int i=0; i<arraySize; i++) {
//         if (inputArray[i] > compareNum) {
//             newSize++;
//         }
//     }
//     int* theNewArray = new int[newSize];
//     int newArrayIndex = 0;
//     for (int i=0; i<arraySize; i++) {
//         if (inputArray[i] > compareNum) {
//             theNewArray[newArrayIndex] = inputArray[i];
//             newArrayIndex++;
//         }
//     }
//     return theNewArray;
// }
//-----------------------------------------------------------------

// Question 2: For a doubly-linked list, write a C++ function to create a new node after a given node value.  The value of the new node should be the sum of the values that are before and after the given node value.  The function arguments are

// head: head of the linked list
// value: value to search for in the linked list
// You can assume the specified value will not be in the head or tail of the LL. Your function should return the head of the linked list.

// struct node
// {
//     int value;
//     node* next;
//     node* prev;
// };

// node* AddNewNodeSum(node* head, int value)
// {
// 	node* newNode = new node;

// 	for (node* currentNode = head; currentNode != nullptr; currentNode = currentNode->next)
// 	{
// 		if (currentNode->value == value)
// 		{
// 			newNode->value = currentNode->next->value + currentNode->prev->value;
// 			newNode->next = currentNode->next;
// 			currentNode->next->prev = newNode;
// 			newNode->prev = currentNode;
// 			currentNode->next = newNode;
// 		}
// 	}
// 	return head;
// }

//-----------------------------------------------------------------
// Author's Solution

// node * AddNewNodeSum(node *head, int value)
// {
//     node* temp = head;
//     while(temp != NULL) {
//         if(temp->value == value){
//             break;
//         }else{

//             temp = temp -> next;
//         }
//     }
    
//     //get sum of prev and next
//     int newID = temp->prev->value + temp->next->value;
    
//     //create new node
//     node* newNode = new node;
//     newNode->value = newID;
//     newNode->prev = temp;
//     newNode->next = temp->next;
//     temp->next = newNode;

//     return head;
// }
//-----------------------------------------------------------------
