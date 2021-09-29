#include <iostream>
#include <stream>

int main() {
	//algorithms are what happen between input and output

	//you have some input, you run it through an algorithm, and, as long as there aren't compiling errors, you get an output

	//algorithms have preconditions and postconditions
	//pre: what must be true in order for the algorithm to produce the desired output
	//post: expected changes/outcome after the algorithm runs

	//for example, sorting an array of integers
	//pre: ?
	//all numbers are integers, there are at least two numbers in the array
	//post: ?
	//numbers are sorted

	//evaluating algorithms
	//what's the MOST important thing?
		//the algorithm needs to be correct
	//if you have multiple algorithms that are correct, how to you determine which is better?
		//runtime
	//the longer the runtime, the greater the cost; we want to minimize cost
	//simple: assign each line of code cost = 1, then count up the number of lines
	//todays computers are pretty fast, so this becomes fairly negligible for code without loops
	//essentially the cost becomes n, where n is the number of lines of code

	//we use what's called Big Oh (O) notation (the letter O) to describe the runtime cost of an algorithm as n goes to infinity


	int intArray[10];
	string socks[10];
	
	//2D arrays
	int aTwoDeeArray[10][10];

	//find something in intArray, which is unsorted

	//find something in socks, also unsorted

	//any difference?

	//what's O(n) for these algorithms? just n

	//find an integer in aTwoDeeArray, again unsorted
	//what's the worst case?
		//n squared

	//what about a 3d unsorted array?
		//n cubed



}