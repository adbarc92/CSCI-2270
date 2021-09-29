#include <iostream>
#include <sstream>
#include <fstream>

#include "Graph.h"

std::pair<int,int> findVertex( std::vector< std::vector< std::string > > adjMatrix, std::string name, int size )
{
	std::pair<int,int> coor;
	coor.first = 0;
	coor.second = 0;

	for (int i = 0; i < adjMatrix.size(); ++i)
	{
		for (int j = 0; j < adjMatrix.size(); ++j)
		{
			std::string city = adjMatrix[ i ][ j ];
			if ( city == name )
			{

				coor.first = i;
				coor.second = j;
				return coor;
			}
		}
	}
	std::cout << "No match found" << std::endl;
	return coor;
}

int findEdge( std::string v1, std::string v2 )
{
	
}

int main( int argc, char* argv[] )
{
	std::string url = argv[ 1 ];
	std::string curLine = "";
	std::string curWord = "";
	std::ifstream inFile ( url );
	std::vector< std::vector< std::string > > graph;
	int i = 0, j = 0;

	while ( getline( inFile, curLine ) )
	{
		std::stringstream ss(curLine);
		while ( getline( ss, curWord, ' ' ))
		{
			graph[i].push_back( curWord );
		}
		i++;
	}

	Graph g;

	for ( unsigned int i = 0; i < graph.size() ; ++i )
	{
		for ( unsigned int j = 0; j < graph.size(); ++j)
		{
			std::string city = graph[i][j];
			if ( city[ 0 ] >= 'A' && city[ 0 ] <= 'Z' )
			{
				g.addVertex( city );
			}
		}
	}

	g.addVertex( "Boulder" );
	g.addVertex( "Denver" );
	g.addVertex( "NewMexico" );
	g.addVertex( "Texas" );

	g.addEdge( "Boulder", "Denver", 30 );
	g.addEdge( "Boulder", "NewMexico", 200 );
	g.addEdge( "Boulder", "Texas", 500 );

	g.addEdge("Denver","Boulder",30);
	g.addEdge("Denver", "NewMexico", 170);
	g.addEdge("Denver", "Texas",400);

	g.addEdge("NewMexico","Boulder",200);
	g.addEdge("NewMexico","Denver",170);
	g.addEdge("NewMexico","Texas",50);

	g.addEdge("Texas","Boulder",500);
	g.addEdge("Texas","Denver",400);
	g.addEdge("Texas","NewMexico",50);
}