#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "MovieTree.hpp"

bool load_movietree( std::string filename, MovieTree& mt )
{
	// Simple test case for debugging
	// mt.addMovieNode( 10, "D", 1995, 1 );

	// mt.addMovieNode( 10, "B", 1995, 1 );
	// mt.addMovieNode( 10, "A", 1995, 1 );
	// mt.addMovieNode( 10, "C", 1995, 1 );

	// mt.addMovieNode( 10, "F", 1995, 1 );
	// mt.addMovieNode( 10, "E", 1995, 1 );
	// mt.addMovieNode( 10, "S", 1995, 1 );

	// mt.addMovieNode( 10, "M", 1995, 1 );
	// mt.addMovieNode( 10, "X", 1995, 1 );

/*
			D
		B 		 F
	A 	  C   	E    S
	              M  X

*/

	std::fstream fs;
	fs.open( filename );

	if( !fs )
	{
		std::cout << "Cannot load movies filed: " << filename << std::endl;
		return false;
	}

	std::string line;
	while( std::getline( fs, line ) )
	{
		std::stringstream ss( line );
		std::string rating;
		std::string title;
		std::string year;
		std::string quant;

		std::getline( ss, rating, ',' );
		std::getline( ss, title, ',' );
		std::getline( ss, year, ',' );
		std::getline( ss, quant, ',' );

		mt.addMovieNode( std::stoi( rating ), title, std::stoi( year ), std::stoi( quant ) );
	}

	return true;
}

int main( int argc, char* argv[] )
{
	if( argc != 2 )
	{
		std::cout << "You must provide 2 arguments." << std::endl;
		return 1;
	}

	MovieTree mt;

	std::string filename = argv[ 1 ];
	if( !load_movietree( filename, mt ) )
	{
		return 1;
	}

	std::string commands[ 7 ] = { //array of strings to be printed
		"======Main Menu======",
		"1. Find a movie",
		"2. Rent a movie",
		"3. Print the inventory",
		"4. Delete a movie",
		"5. Count the movies",
		"6. Quit"
	};

	bool running = true;
	int cmd = 0;
	while( running )
	{
		for( int i = 0; i < 7; i++ )
		{
			std::cout << commands[ i ] << std::endl;
		}
		std::cin >> cmd;
		if( cmd == 1 )
		{
			std::string title;
			std::cout << "Enter title: ";
			std::cin.ignore();
			std::getline( std::cin, title );

			mt.findMovie( title );
		}
		else if( cmd == 2 )
		{
			std::string title;
			std::cout << "Enter title: ";
			std::cin.ignore();
			std::getline( std::cin, title );

			mt.rentMovie( title );
		}
		else if( cmd == 3 )
		{
			mt.printMovieInventory();
		}
		else if( cmd == 4 )
		{
			std::string title;
			std::cout << "Enter title: ";
			std::cin.ignore();
			std::getline( std::cin, title );

			mt.deleteMovieNode( title );
		}
		else if( cmd == 5 )
		{
			std::cout << "Tree contains: " << mt.countMovieNodes() << " movies." << std::endl; 
		}
		else if( cmd == 6 )
		{
			running = false;
			std::cout << "Goodbye!" << std::endl;
		}
	}

}
