#include <iostream>
#include <vector>

struct vertex;

struct adjVertex
{
	vertex* v;
	int weight;
};

struct vertex
{
	std::string key;
	std::vector<adjVertex> adjacent;
};

class Graph // Weighted graph
{
private:
	// vertices
	std::vector<vertex> vertices;
	vertex* findVertex( std::string );
public:
	// methods for accessing graphs
	Graph();
	~Graph();
	void insertVertex( std::string ); // Identifier of the vertex
	void insertEdge( std::string, std::string, int ); // Start, end, weight
	void printGraph();
};

Graph::Graph(){}

Graph::~Graph(){}

void Graph::insertVertex( std::string value )
{
	bool found = false;
	int i = 0;
	while ( i < vertices.size() && !found)
	{
		if ( vertices[i].key == value )
		{
			found = true;
		}
		i++;
	}
	if ( !found )
	{
		vertex v; // Works despite the fact that it is not dynamically-allocated
		v.key = value;
		vertices.push_back( v );
	}
	else
		std::cout << "There is already a vertex " << value << " in this graph" << std::endl;
}

vertex* Graph::findVertex( std::string value )
{
	int i = 0;
	while ( i < vertices.size() )
	{
		if ( vertices[i].key == value )
		{
			return &vertices[i];
		}
		i++;
	}
	return nullptr;
}

void Graph::insertEdge( std::string v1, std::string v2, int weight )
{
	vertex* vStart = findVertex( v1 );
	vertex* vEnd = findVertex( v2 );
	
	if ( vStart != nullptr && vEnd != nullptr ) // Both vertices exist and thus can be connected
	{
		// Assumes edge does not exist
		adjVertex v1v2Edge;
		v1v2Edge.weight = weight;
		v1v2Edge.v = vEnd;
		vStart->adjacent.push_back( v1v2Edge );
	}
	
	else
	{
		if ( vStart == nullptr )
		{
			std::cout << "No vertex with name " << v1 << " in this graph" << std::endl;
		}
		if ( vEnd == nullptr )
		{
			std::cout << "No vertex with name " << v2 << " in this graph" << std::endl;
		}
	}
}

void vectorTest()
{
	std::vector<int> bunchaInts;
	bunchaInts.push_back( 5 ); // inserts to vector at end
	bunchaInts.push_back( 10 );
	bunchaInts.push_back( 4 );
	bunchaInts.push_back( 6 );
	bunchaInts.push_back( 8 );

	for (int i = 0; i < bunchaInts.size(); ++i)
	{
		std::cout << "Item " << i << " is " << bunchaInts[ i ] << std::endl;
	}
}

int main()
{
	Graph myGraph;
	myGraph.insertVertex( "South Boulder" );
	myGraph.insertVertex( "Glacier Ice Cream" );
	myGraph.insertVertex( "Golden" );
	myGraph.insertVertex( "Superior" );
	myGraph.insertVertex( "Superior Costco" );
	myGraph.insertVertex( "Wildwood Guitars" );
	myGraph.insertVertex( "Denver" );
	myGraph.insertVertex( "Rep Fitness" );
	myGraph.insertVertex( "IKEA" );

	myGraph.insertEdge( "South Boulder", "Glacier Ice Cream", 1 );
		myGraph.insertEdge( "Glacier Ice Cream", "South Boulder", 1 );
	myGraph.insertEdge( "South Boulder", "Superior", 5 );
	myGraph.insertEdge( "South Boulder", "Golden", 15 );
		myGraph.insertEdge( "Golden", "South Boulder", 15 );
	myGraph.insertEdge( "Superior", "Superior Costco", 1 );
	myGraph.insertEdge( "Superior", "South Boulder", 5 );
	myGraph.insertEdge( "Superior Costco", "Superior", 1 );
	myGraph.insertEdge( "Superior", "Wildwood Guitars", 1 );
	myGraph.insertEdge( "Superior", "Denver", 10 );
	myGraph.insertEdge( "Denver", "Superior", 10 );
	myGraph.insertEdge( "Denver", "Golden", 15 );
	myGraph.insertEdge( "Denver", "Rep Fitness", 3 );
	myGraph.insertEdge( "Denver", "IKEA", 20 );









}