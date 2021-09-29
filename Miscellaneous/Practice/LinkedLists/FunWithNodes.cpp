#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

//----------------------------------------------------------------------------------------
// Class Definitions
//----------------------------------------------------------------------------------------

struct city
{
	std::string cityName;
	city* next;
	std::string message;
	
	city(){};
	city(std::string initName, city* initNext, std::string initMessage)
	{
		cityName = initName;
		next = initNext;
		message = initMessage;
	}
};
//----------------------------------------------------------------------------------------
// Functions - Required
//----------------------------------------------------------------------------------------

city* addCity (city* head, city* previous, std::string cityName)
{
	if (head == nullptr)
	{
		head = new city;
		head->cityName = cityName;
		head->next = nullptr;
		return head;
	}
	else
	{
		city* currentCity = head;
		while (currentCity != previous)
		{
			currentCity = currentCity->next;
		}
		city* newCity = new city;
		newCity->cityName = cityName;
		newCity->next = previous->next;
		previous->next = newCity;
	}
	return head;
}

city* buildNetwork()
{
	std::string cityNames[11] = {"Los Angeles" , "Phoenix" , "Denver", "Dallas" , "St. Louis" , "Chicago" , "Atlanta" , "Washington, D.C." , "New York" , "Boston" , ""};
	city* head = new city;
	city* previous = new city;
	int i = 0;

	while (cityNames[i] != "")
	{
		addCity(head, previous, cityNames[i]);
		previous = previous->next;
		++i;
	}
	return head;
}

void transmitMsg(city* head)
{
	std::ifstream inFile;
	std::string word;
	city* currentCity = head;
	
	inFile.open ("messageIn.txt");
	
	if ( !inFile )
	{
		std::cout << "Unable to open file: messageIn.txt" << std::endl;
		return;
	}

	while (inFile >> word)
	{
		std::cout << "Word: " << word << std::endl;
		while (currentCity->next != nullptr)
		{
			std::cout << currentCity->cityName << " received " << word << std::endl;
		}
	}
}

void printPath (city* head)
{
	if (head == nullptr)
	{
		std::cout << "There are no available cities." << std::endl;
	}
	else
	{
		city* currentCity = head;
		std::cout << "===CURRENT PATH===" << std::endl;
		while (currentCity->next != nullptr)
		{
			std::cout << currentCity->cityName << " -> ";
			currentCity = currentCity->next;
		}
	}
}

//----------------------------------------------------------------------------------------
// Functions - Optional
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// Main
//----------------------------------------------------------------------------------------

int main()
{
	// Variable Declaration
	int menuOption;
	city* head = new city;
	city* previous = new city;
	head = nullptr;
	previous = nullptr;

	return 0;
	
	std::string cityNew, cityPrevious;

	std::cout << "======Main Menu======" << std::endl;
	std::cout << "1. Build Network" << std::endl;
	std::cout << "2. Print Network Path" << std::endl;
	std::cout << "3. Transmit Message Coast-to-Coast" << std::endl;
	std::cout << "4. Add City" << std::endl;
	std::cout << "5. Quit" << std::endl;

	std::cin >> menuOption;

	if (menuOption < 1 || menuOption > 5)
	{
		std::cout << "I'm sorry, that is not a valid menu option." << std::endl;
		return 1;
	}

	switch (menuOption)
	{
		case 1:
			head = buildNetwork();
			break;
		case 2:
			printPath(head);
			break;
		case 3: 
			transmitMsg(head);
			break;
		case 4: 
			std::cout << "Enter a city name: " << std::endl;
			getline(std::cin,cityNew);
			std::cout << "Enter a previous city name: " << std::endl;
			getline(std::cin,cityPrevious);
			addCity(head, previous, cityNew); // Will not work yet
			break;
		case 5:
			std::cout << "Goodbye!" <<std::endl;
			return 0;
	}
	return 0;
}

// Previous should be managed outside of function
// Destructor
// For general insertion, the LL must always be iterated through;
// Shift+Tab = unindent

// Notes
	// 