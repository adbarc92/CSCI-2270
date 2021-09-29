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
	city* newCity = new city;
	newCity->cityName = cityName;
	newCity->next = nullptr;
	if (head == nullptr)
	{
		return newCity;
	}
	else if (previous == nullptr)
	{
		newCity->next = head;
		return newCity;
	}
	else
	{
		newCity->next = previous->next;
		previous->next = newCity;
		return head;
	}
}

city* buildNetwork()
{
	city* head = new city;
	head->cityName = "Los Angeles";
	head->next = nullptr;

	std::string cityNames[10] = {
		"Los Angeles", 
		"Phoenix", 
		"Denver",
		"Dallas" , 
		"St. Louis",
		"Chicago" , 
		"Atlanta" , 
		"Washington, D.C." , 
		"New York" , 
		"Boston"
	};

	city* previous = head;
	for (int i = 1; i < 10 ; ++i)
	{
		city* newCity = new city;
		newCity->cityName = cityNames[i];
		newCity->next = nullptr;
		previous->next = newCity;

		previous = newCity;
	}
	return head;
}

void transmitMsg(city* head)
{
	std::ifstream inFile;
	std::string word;
	std::string url = "messageIn.txt";

	inFile.open( url );

	if ( !inFile )
	{
		std::cout << "Unable to open file: messageIn.txt" << std::endl;
	}

	while ( getline( inFile, word, ' ' ) )
	{
		city* previous = nullptr;
		for (city* currentCity = head; currentCity != nullptr; currentCity = currentCity->next)
		{
			currentCity->message = word;
			std::cout << currentCity->cityName << " received " << currentCity->message << std::endl;
			if (previous != nullptr)
			{
				previous->message = "";
			}
			previous = currentCity;
		}
		previous->message = "";
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
		std::cout << "===CURRENT PATH===" << std::endl;
		for (city* currentCity = head; currentCity != nullptr; currentCity = currentCity->next)
		{
				std::cout << currentCity->cityName << " -> ";
		}
		std::cout << "NULL" << std::endl << "==================" << std::endl;
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
	std::string cityName, prevCityName;
	std::string cityNew, cityPrevious;

	while (true)
	{
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
			continue;
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
				std::cin >> cityName;
				std::cout << "Enter a previous city name: " << std::endl;
				std::cin >> prevCityName;

				if (prevCityName == "First")
				{
					city* newCity = new city;
					newCity->next = head;
					head = newCity;
					head->cityName = cityName;
					break;
				}
				
				for (city* currentCity = head; currentCity != nullptr; currentCity = currentCity->next)
				{
					if (currentCity->cityName == prevCityName)
					{
						addCity(head, currentCity, cityName);
					}
				}
				break;
			case 5:
				std::cout << "Goodbye!" <<std::endl;
				return 0;
		}
	}
	return 0;
}

// Previous should be managed outside of function
// Destructor
// For general insertion, the LL must always be iterated through;
// Shift+Tab = unindent

// Notes
	// TransmitMSG is not 100% correct
	// Switch needs to add a city to the front