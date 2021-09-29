#include "Graph.hpp"
#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

int find_vertex_index( std::string city_name, std::vector< vertex >& vertices ){
	for( int i = 0; i < (int)vertices.size(); i++ )
	{
		vertex& v = vertices[ i ];
		if( v.name == city_name )
		{
			return i;
		}
	}
	return -1;
};

int find_vertex_with_lowest_weight( std::vector< vertex* >& vertices )
{
	int ind = -1;
	int min = std::numeric_limits< int >::max();
	for( int i = 0; i < (int)vertices.size(); i++ )
	{
		if( vertices[ i ]->weightedDistance < min )
		{
			min =  vertices[ i ]->weightedDistance;
			ind = i;
		}
	}
	return ind;
}

Graph::Graph() {}

Graph::~Graph()
{
	// dtor
}
void Graph::addEdge(string v1, string v2, int weight)
{
	for( unsigned int i = 0; i < vertices.size(); i++ )
	{
		if( vertices[i].name == v1 )
		{
			for( unsigned int j = 0; j < vertices.size(); j++ )
			{
				if( vertices[j].name == v2 && i != j )
				{
					adjVertex av;
					av.v = &vertices[j];
					av.weight = weight;
					vertices[i].adj.push_back(av);
				}
			}
		}
	}
}
void Graph::addVertex(string n)
{
	bool found = false;
	for( unsigned int i = 0; i < vertices.size(); i++ )
	{
		if( vertices[i].name == n )
		{
			found = true;
			cout << vertices[i].name << " found." << endl;
		}
	}
	if( found == false )
	{
		vertex v;
		v.name = n;
		v.districtID = -1;
		v.visited = false;
		v.unweightedDistance = 0;
		v.weightedDistance = 0;
		v.parent = nullptr;
		vertices.push_back(v);
	}
}

void Graph::displayEdges()
{
	for( vertex& v: vertices )
	{
		cout << v.districtID << ":" << v.name << "-->";
		for( unsigned int j = 0; j < v.adj.size(); j++ )
		{
			cout << ( j ? "***" : "" ) << v.adj[ j ].v->name;
		}
		cout << endl;
	}
}

void Graph::assignDistricts()
{
	// For each vertex in the graph, set the district if it has not already been set
	int district_id = 1;
	for( vertex& v: vertices )
	{
		if( v.districtID == -1 )
		{
			DFSLabel( v.name, district_id );
			district_id++;
		}
		v.visited = false;
	}
}

void Graph::DFSLabel( std::string startingCity, int distID )
{
	// This is basically the same as iterating left-to-right over a tree
	int i = find_vertex_index( startingCity, vertices );
	vertex& v = vertices[ i ];
	v.visited = true;
	v.districtID = distID;
	for( adjVertex& adj: v.adj )
	{
		if( !adj.v->visited ){
			DFSLabel( adj.v->name, distID );
		}
	}
}

void Graph::shortestPath( std::string startingCity, std::string endingCity )
{
	// Step 0: Make sure arguments are valid
	int i_start = find_vertex_index( startingCity, vertices );
	int i_end = find_vertex_index( endingCity, vertices );
	if( i_start == -1 )
	{
		std::cout << "One or more cities doesn't exist" << std::endl;
		return;
	}
	if( i_end == -1 )
	{
		std::cout << "One or more cities doesn't exist" << std::endl;
		return;
	}

	vertex& start = vertices[ i_start ];
	vertex& end = vertices[ i_end ];

	if( start.districtID == -1 || end.districtID == -1 )
	{
		std::cout << "Please identify the districts before checking distances" << std::endl; 
	}
	if( start.districtID != end.districtID )
	{
		std::cout << "No safe path between cities" << std::endl;
		return;
	}

	// Step 1: create a queue and add the current vertex to it, mark this vertex as visited
	std::queue< vertex* > Q;
	start.parent = nullptr;
	start.visited = true;
	Q.push( &start );

	while( !Q.empty() )
	{
		// Step 2: get the vertex at the front of the queue and remove it from the queue
		vertex* v = Q.front();
		Q.pop();

		// If this is the vertex you're seeking, then your donzo
		if( v == &end )
		{
			break;
		}

		// Step 3: For each adjacent vertex...
		for( adjVertex& adj: v->adj )
		{
			// Only if you have not visited this adjacent vertex
			if( !adj.v->visited )
			{
				// Add this vertex to the queue, mark it as visited
				adj.v->parent = v;
				adj.v->visited = true;
				Q.push( adj.v );
			}
		}
	}

	// The reference "end" above is the destination vertex, and the parent has been tracked
	// each time a vertex was inserted into Q.  So if you start at end and iterate through it's 'parent'
	// you will get to 'start' and thus have a path, but it will be backwards.
	std::vector< std::string > path;
	vertex* v = &end;
	while( v->parent )
	{
		path.push_back( v->name );
		v = v->parent;
	}
	path.push_back( v->name );

	// Since the path is backwards, go through the path backwards and print it so it is forwards.
	std::cout << path.size() - 1;
	for( int i = path.size() - 1; i >= 0; i-- )
	{
		std::cout << ", " << path[ i ];
	}
	std::cout << std::endl;

	for( vertex& v: vertices )
	{
		v.visited = false;
		v.parent = nullptr;
	}
}

void Graph::shortestWeightedPath(std::string startingCity, std::string endingCity)
{
	// Step 0: Make sure arguments are valid
	int i_start = find_vertex_index( startingCity, vertices );
	int i_end = find_vertex_index( endingCity, vertices );
	if( i_start == -1 )
	{
		std::cout << "One or more cities doesn't exist" << std::endl;
		return;
	}
	if( i_end == -1 )
	{
		std::cout << "One or more cities doesn't exist" << std::endl;
		return;
	}

	vertex& start = vertices[ i_start ];
	vertex& end = vertices[ i_end ];

	if( start.districtID == -1 || end.districtID == -1 )
	{
		std::cout << "Please identify the districts before checking distances" << std::endl;
		return;
	}
	if( start.districtID != end.districtID )
	{
		std::cout << "No safe path between cities" << std::endl;
		return;
	}

	// Step 1: set all vertices on the graph to have "infinite" weight.  Here they are all
	// just being set to the maximum value an int can hold, which is basically infinity
	for( vertex& v: vertices )
	{
		v.weightedDistance = std::numeric_limits< int >::max();
	}

	// Step 2: create a list (this is just a vector) and add the current vertex to it, 
	// mark this vertex as visited, and set its distance to 0
	std::vector< vertex* > list;
	start.parent = nullptr;
	start.visited = true;
	start.weightedDistance = 0;
	list.push_back( &start );

	// As long as there are vertices in the list with less than infinite weight...
	int next_index = 0;
	while( next_index != -1 )
	{
		// Step 3: find the vertex in the list with the lowest weight and remove it
		// from the list, this is the 'current' vertex
		next_index = find_vertex_with_lowest_weight( list );
		vertex* v = list[ next_index ];
		list.erase( list.begin() + next_index );

		// If this is the vertex you're seeking, then your donzo
		if( v == &end )
		{
			break;
		}

		// Step 4: For each adjacent vertex...
		for( adjVertex& adj: v->adj )
		{
			// Calculate the distance through the current vertex to the adjacent vertex,
			// this is just the current vertex's makred distance plus the weight of the edge
			int dist = v->weightedDistance + adj.weight;

			// If the distance calculated is less than the distance marked in the adjacent vertex,
			// then set the adjacent vertex's distance to what was just calculated, and
			// remember to change the parent to the current vertex.  This will always happen
			// the first time because of Step 1.
			if( adj.v->weightedDistance > dist )
			{
				adj.v->weightedDistance = dist;
				adj.v->parent = v;
			}

			// If the adjacent vertex has not been visited before, then add it to the list
			// and mark it as visited.
			if( !adj.v->visited )
			{
				adj.v->parent = v;
				adj.v->visited = true;
				list.push_back( adj.v );
			}
		}
	}

	// The reference "end" above is the destination vertex, and the parent has been tracked
	// each time a vertex was inserted into Q.  So if you start at end and iterate through it's 'parent'
	// you will get to 'start' and thus have a path, but it will be backwards.
	std::vector< std::string > path;
	vertex* v = &end;
	while( v->parent )
	{
		path.push_back( v->name );
		v = v->parent;
	}
	path.push_back( v->name );

	// Since the path is backwards, go through the path backwards and print it so it is forwards.
	// The final cost is the distance marked in the last vertex, thanks Dijkstra!
	std::cout << end.weightedDistance;
	for( int i = path.size() - 1; i >= 0; i-- )
	{
		std::cout << ", " << path[ i ];
	}
	std::cout << std::endl;

	// Don't forget to reset everything, or this function will only work once
	for( vertex& v: vertices )
	{
		v.visited = false;
		v.parent = nullptr;
	}
}
