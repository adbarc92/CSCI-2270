#include <iostream>
#include <fstream>
#include <sstream>
#include "MovieTree.hpp"

int main( int argc, char *argv[] )
{
	std::string menu[ 6 ] = { "Find a movie", "Rent a movie", "Print the inventory", "Delete a movie", "Quit" };
	bool running = true;
	int choice = 0;
	std::string title = "", curLine = "";
	std::ifstream infile( argv[ 1 ] );
	MovieTree mt;

	while( getline( infile, curLine ))
	{
		std::stringstream curStrStream( curLine );
		std::string ranking = "";
		std::string releaseYear = "";
		std::string quantity = "";
		getline(curStrStream,ranking,',');
		getline(curStrStream,title,',');
		getline(curStrStream,releaseYear,',');
		getline(curStrStream,quantity,',');
		mt.addMovieNode( stoi( ranking ), title, stoi( releaseYear ), stoi( quantity ) );
	}
	while ( running ) 
	{
		std::cout << "======Main Menu======" << std::endl;
		for (int i = 0; i < 6; ++i)
		{
			std::cout << ( i + 1 ) << ". " << menu[ i ] << std::endl;
		}
		std::cin >> choice;
		switch( choice )
		{
			case 1:
				std::cout << "Enter title:" << std::endl;	
				std::cin >> title;
				mt.findMovie( title );
			case 2:
				std::cin >> title;
				mt.rentMovie( title );
			case 3:
				mt.printMovieInventory();
			case 4:
				std::cout << "Enter title:" << std::endl;
				std::cin >> title;
				mt.deleteMovieNode( title );
			case 5:
				mt.countMovieNodes();
			case 6:
				std::cout << "Goodbye!" << std::endl;
				running = false;
		}
	}
	return 0;
}

