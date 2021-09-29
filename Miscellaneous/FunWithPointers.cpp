#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

int main ()
{
// References
	// int firstInt, secondInt;
	// firstInt = 10;
	// secondInt = 5;
	// int &firstRef = firstInt;
	// int &secondRef = secondInt;
	
	// std::cout << "FirstInt is " << firstInt << " and SecondInt is " << secondInt << std::endl;

	// std::cout << "FirstRef is " << firstRef << " and SecondRef is " << secondRef << std::endl;

	// secondRef = firstInt;

	// std::cout << "FirstInt is " << firstInt << " and SecondInt is " << secondInt << std::endl;

	// std::cout << "FirstRef is " << firstRef << " and SecondRef is " << secondRef << std::endl;

// Pointers
	int firstInt, secondInt;
	firstInt = 10;
	secondInt = 5;
	int *firstPtr = &firstInt;
	int *secondPtr = &secondInt;
	
	std::cout << "FirstInt is " << firstInt << " and SecondInt is " << secondInt << std::endl;

	std::cout << "FirstRef is " << firstPtr << " and SecondRef is " << secondPtr << std::endl;

	*secondPtr = firstInt; // Reassigns memory indicated by SecondPtr to equal FirstInt;

	std::cout << "FirstInt is " << firstInt << " and SecondInt is " << secondInt << std::endl;

	std::cout << "FirstRef is " << firstPtr << " and SecondRef is " << secondPtr << std::endl;

	secondPtr = &firstInt;

	int* firstPtr, secondPtr;
	*firstPtr = 6;
	*secondPtr = 9;
	secondPtr = firstPtr;
	std:cout << "FirstPtr is " << " and SecondPtr is " << secondPtr << std::endl;

}