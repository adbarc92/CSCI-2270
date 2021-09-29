#include <iostream>
#include <fstream>
#include <sstream>

#include "Graph.hpp"

#include <iostream>
#include <utility>

bool load_graph( std::string fileName, Graph& g )
{
	std::ifstream fs( fileName );
	std::stringstream ss;
	fs.open( fileName );

	if( !fs )
	{
		std::cout << "Cannot read graph file: " << fileName << std::endl;
		return false;
	}

	std::vector< std::string > cities;

	// read head of file with all city names into string "city_name_list"
	std::string city_name_list;
	std::getline( fs, city_name_list );

	// iterate over city_name_list and add vertex for each city
	ss.str( city_name_list );
	std::string city_name;
	std::getline( ss, city_name, ',' ); // first thing is just the word "cities", not a city name, so ignore it
	while( std::getline( ss, city_name, ',' ) ) //city names are seperated by a comma
	{
		cities.push_back( city_name );
		g.addVertex( city_name );
	}

	// read the rest of the lines in the file, adding edges
	std::string line;
	while( std::getline( fs, line ) )
	{
		ss.clear();
		ss.str( line );
		std::string city_name = "";
		std::getline( ss, city_name, ',' );
		std::string weight_str;
		int i = 0;
		while( std::getline( ss, weight_str, ',' ) )
		{
			int weight = std::stoi( weight_str );
			if( weight > 0 )
			{
				g.addEdge( city_name, cities[ i ], weight );
			}
			i++;
		}
	}

	return true;
}

void print_menu()
{
	std::cout << "======Main Menu======" << std::endl;
	std::cout << "1. Print vertices" << std::endl;
	std::cout << "2. Find districts" << std::endl;
	std::cout << "3. Find shortest path" << std::endl;
	std::cout << "4. Find shortest weighted path" << std::endl;
	std::cout << "5. Quit" << std::endl;
}

std::pair< std::string, std::string > read_cities_from_stdin()
{
	std::string city1, city2;
	std::cout << "Enter a starting city: " << std::endl;
	std::cin.ignore(); // idk why, but i need this ignore or it doesnt work
	std::getline( std::cin, city1 );

	std::cout << "Enter an ending city: " << std::endl;
	std::getline( std::cin, city2 );

	return std::make_pair( city1, city2 );
}

int main( int argc, char* argv[] )
{
	Graph g;

	if( argc != 2 )
	{
		std::cout << "You must provide the filename as an argument." << std::endl;
		return 1;
	}

	std::string filename = argv[ 1 ];
	if( !load_graph( filename, g ) )
	{
		return 1;
	}

	bool running = true;
	std::string cmd;

	while( running )
	{
		print_menu();

		std::cin >> cmd;
		if( cmd == "1" )
		{
			g.displayEdges();
		}
		if( cmd == "2" )
		{
			g.assignDistricts();
		}
		if( cmd == "3" )
		{
			std::pair< std::string, std::string > city_names = read_cities_from_stdin();
			g.shortestPath( city_names.first, city_names.second );
		}
		if( cmd == "4" )
		{
			std::pair< std::string, std::string > city_names = read_cities_from_stdin();
			g.shortestWeightedPath( city_names.first, city_names.second );			
		}
		if( cmd == "5" )
		{
			std::cout << "Goodbye!" << std::endl;
			running = false;
		}
	}

	return 0;
}