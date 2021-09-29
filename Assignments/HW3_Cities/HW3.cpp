#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

struct city {
	std::string cityName;
	std::string message;
	city* next;
	city(){}
	city( std::string initName, city* initNext, std::string initMessage )
	{
		cityName = initName;
		message = initMessage;
		next = initNext;
	}
};

void printPath( city* head )
{
	if( head == nullptr )
	{
		std::cout << "No path built." << std::endl;
		return;
	}
	std::cout << "===CURRENT PATH===" << std::endl;
	for( city* curr = head; curr != nullptr; curr = curr->next )
	{
		if( curr->next != nullptr )
		{
			std::cout << curr->cityName << " -> ";
		}
		else
		{
			std::cout << curr->cityName << " -> NULL" << std::endl;
		}
	}
	std::cout << "===================" << std::endl;
}

city* buildNetwork()
{
	std::string cities[] = {
		"Los Angeles",
		"Phoenix",
		"Denver",
		"Dallas",
		"St. Louis",
		"Chicago",
		"Atlanta",
		"Washington, D.C.",
		"New York",
		"Boston"
	};
	
	city* ret = new city();
	ret->cityName = cities[ 0 ];
	ret->next = nullptr;
	city* curr = ret;
	for( int i = 1; i < 10; i++ )
	{
		city* next = new city();
		next->cityName = cities[ i ];
		next->next = nullptr;
		curr->next = next;
		
		curr = next;
	}
	
	printPath( ret );
	
	return ret;
}

city* addCity( city* head, city* previous, std::string cityName )
{
	city* curr = new city();
	curr->cityName = cityName;
	
	if( head == nullptr )
	{
		return curr;
	}
	if( previous == nullptr )
	{
		curr->next = head;
		return curr;
	}
	else
	{
		curr->next = previous->next;
		previous->next = curr;
	}
	return head;
}

void transmitMsg( city* head )
{
	if( head == nullptr )
	{
		std::cout << "No path has been built." << std::endl;
		return;
	}
	std::fstream ifs( "message.txt" );
	
	if( !ifs )
	{
		std::cout << "No message to be trasmitted." << std::endl;
		return;
	}
	
	std::string line;
	while( std::getline( ifs, line, ' ' ) )
	{
		city* prev = nullptr;
		for( city* curr = head; curr != nullptr; curr = curr->next )
		{
			curr->message = line;
			std::cout << curr->cityName << " received " << curr->message << std::endl;
			if( prev != nullptr )
			{
				prev->message = "";
			}
			prev = curr;
		}
		prev->message = "";
	}
}

int main()
{
	city* head = nullptr;
	bool running = true;

	head = addCity( head, nullptr, "Denver" );

	return 0;

	while( running )
	{
		std::cout << "======Main Menu======" << std::endl;
		std::cout << "1. Build Network" << std::endl;
		std::cout << "2. Print Network Path" << std::endl;
		std::cout << "3. Transmit Message Coast-To-Coast" << std::endl;
		std::cout << "4. Add City" << std::endl;
		std::cout << "5. Quit" << std::endl;
		
		std::string inp;
		int cmd = 5;
		std::cin >> inp;
		cmd = std::stoi( inp );
		
		if( cmd == 1 )
		{
			head = buildNetwork();
		}
		if( cmd == 2 )
		{
			printPath( head );
		}
		if( cmd == 3 )
		{
			transmitMsg( head );
		}
		if( cmd == 4 )
		{
			std::string cityName;
			std::string prevCityName;
			std::cout << "Enter a city name" << std::endl;
			std::cin >> cityName;
			std::cout << "Enter a previous city name" << std::endl;
			std::cin >> prevCityName;
			if( prevCityName == "First" )
			{
				city* curr = new city();
				curr->cityName = cityName;
				curr->next = head;
				head = curr;
			}
			else
			{
				for( city* curr = head; curr != nullptr; curr = curr->next )
				{
					if( curr->cityName == prevCityName )
					{
						head = addCity( head, curr, cityName );
						break;
					}
					else
					{
						std::cout << "ERROR: No city with a matching name." << std::endl;
						break;
					}
				}
			}
		}
		if( cmd == 5 )
		{
			std::cout << "Goodbye!" << std::endl;
			running = false;
		}
	}
	return 0;
}
