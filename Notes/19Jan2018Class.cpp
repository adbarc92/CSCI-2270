#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int addTwoNums(int first, int second); // Declaring the prototype here allows the code to be positioned below main and still function;

int main()
{
	// Variables
	int anInt = 7; 
	float aFloat = 7.5; // Declaring an int to store a decimal will not round, it will just cut the decimal off
	double aDouble =19.2345;
	int intArray[10];

	std::string socks[10];
	socks[0] = "blue";
	socks[1] = "red";
	char myChar = 'a';

	// 2D Arrays
	int aTwoDeeArray[10][10]; //Typically, first is rows, second is columns, but it ultimately doesn't matter

	// 
	std::string girlsName = "arya";
	if (girlsName == "arya") std::cout << "a girl is no one" << std::endl; // This will still run
	else if (girlsName == "waif")
	{
		std::cout << "SPOILER ALERT\n"; // Alternate linebreak
	}
	else
		std::cout << "i don't know who you are" << std::endl;

// Loops: For Loop for specific number of iterations, While Loop for an unknown number

	// For Loops
	for (int i = 0; i < 10; ++i) // This variable, i, has a SCOPE restricted to this For Loop
	{
		for (int j = 0; j < 10; ++j) // Nested For Loops
		{
			aTwoDeeArray[i][j] = i*j;
			std::cout << addTwoNums(i,j) << std::endl;
			addTwoNums(i,j); // Added for function demonstration
		}
		std::cout << "I is" << i << std::endl;
	}

	// While Loops
	int counter = 0;
	while (counter < 10)
	{
		std::cout << "counter is " << ++counter << std::endl; // A pre-operation incrementer; position matters because it determines order of execution
	}
}

// Functions
int addTwoNums(int first, int second)
{
	return first + second;
}