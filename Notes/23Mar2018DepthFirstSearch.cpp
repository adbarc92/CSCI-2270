#include <iostream>
#include <vector>
#include <queue>
#include <stack>

// DFS: ordering of paths does not matter - absolute deepest is not necessarily first, it simply goes right to left

struct vertex;

struct adjVertex
{
	vertex* v;
	int weight;
};

struct vertex
{
	std::string key;
	std::vector< adjVertex > adjacent;
	bool visited = false;
	int distance;
	vertex* parent; // Added for BFPath
	bool solved; // Added for Dijkstra's
};

class Graph
{
private:
	std::vector< vertex > vertices;
	vertex* findVertex( std::string );
	void DFS( vertex* );
public:
	Graph();
	~Graph();
	void insertVertex( std::string );
	void insertEdge( std::string, std::string, int );
	void printGraph();
	void BFTraversal( std::string ); // Argument: start node
	void DFSearch( std::string ); // Argument: start node
	void DFSearchNR( std::string ); // Argument: start node
	void resetGraph();
	int BFTdistanceBetween ( std::string, std::string );
	void BFPath( std::string, std::string );
	void dijkstra( std::string, std::string );
};

Graph::Graph(){}
Graph::~Graph(){}

void Graph::resetGraph()
{
	for ( int i = 0; i < vertices.size(); ++i )
	{
		vertices[i].visited = false;
		vertices[i].parent = nullptr; // Added for Dijkstra's
		vertices[i].solved = false; // Added for Dijkstra's
		vertices[i].distance = -1; // Added for Dijkstra's
	}
}

void Graph::insertVertex( std::string value) {
	bool found = false;
	int i=0;
	while (i<vertices.size() && !found) {
		if (vertices[i].key == value) {
			found = true;
		}
		i++;
	}
	if (!found) {
		vertex v;
		v.key = value;
		vertices.push_back(v);
	}
	else {
		std::cout << "There is already a vertex " << value << " in this graph" << std::endl;
	}
}

vertex* Graph::findVertex( std::string value) {
	int i=0;
	while (i<vertices.size()) {
		if (vertices[i].key == value) {
			return &vertices[i];
		}
		i++;
	}
	return nullptr;
}



void Graph::insertEdge( std::string v1, std::string v2, int weight) {
	vertex *vStart = findVertex(v1);
	vertex *vEnd = findVertex(v2);
	if (vStart!=nullptr && vEnd!=nullptr) {
		//this code assumes that an edge doesn't exist
		//write some error checking to handle when it does
		adjVertex v1v2Edge;
		v1v2Edge.weight = weight;
		v1v2Edge.v = vEnd;
		vStart->adjacent.push_back(v1v2Edge);
	}
	else {
		if (vStart == nullptr) {
			std::cout << "no vertex with name " << v1 << " in this graph" << std::endl;
		}
		if (vEnd == nullptr) {
			std::cout << "no vertex with name " << v2 << " in this graph" << std::endl;
		}
	}
}

void Graph::BFTraversal( std::string vertName) {
	std::queue<vertex*> vertexQ;
	vertex* currentVert = findVertex(vertName);
	if (currentVert != nullptr) {
		currentVert->visited = true;
		vertexQ.push(currentVert);
		while (vertexQ.size()!=0) {
			vertex* curV = vertexQ.front();	//like peek
			vertexQ.pop();	//like dequeue
			for (int i=0; i<curV->adjacent.size(); i++) {
				if (!curV->adjacent[i].v->visited) {
					curV->adjacent[i].v->visited = true;
					std::cout << "just visited " << curV->adjacent[i].v->key << std::endl;
					vertexQ.push(curV->adjacent[i].v);
				}
			}
		}
	}
	else {
		std::cout << "vertex " << vertName << " not in graph" << std::endl;
	}
}

void Graph::DFS( vertex* curV )
{
	curV->visited = true;
	for (int i = 0; i < curV->adjacent.size(); ++i) // Iterate through adjacency list
	{
		if ( !curV->adjacent[i].v->visited )
		{
			std::cout << "Just visited " << curV->adjacent[i].v->key << std::endl;
			DFS( curV->adjacent[i].v );
		}
	}
}

void Graph::DFSearch( std::string vertName ) // Public-facing wrapper
{
	vertex* currentVert = findVertex( vertName );
	if ( currentVert != nullptr )
	{
		std::cout << "Starting depth-first search at " << vertName << std::endl;
		DFS( currentVert );
	}
	else
	{
		// Output error message
	}
}

void Graph::DFSearchNR( std::string vertName ) // Non-recursive depth-first search
{
	vertex* currentVert = findVertex( vertName );
	if ( currentVert != nullptr )
	{
		currentVert->visited = true;
		std::cout << "Starting non-recursive depth-first search" << std::endl;
		std::stack< vertex* > vertStack;
		vertStack.push( currentVert );
		while ( !vertStack.empty() )
		{
			vertex* curV = vertStack.top(); // like peek; returns the value
			vertStack.pop(); // Removes the value, does not return it;
			std::cout << "Just visited " << curV->key << std::endl;
			for (int i = 0; i < curV->adjacent.size(); ++i) // Iterate through adjacency list
			{
				if ( !curV->adjacent[i].v->visited ) // If not visited, mark as visited and add to stack
				{
					curV->adjacent[i].v->visited = true;
					vertStack.push( curV->adjacent[i].v );
				}
			}
		}
	}
	else
	{
		// Output error message
	}
}

int Graph::BFTdistanceBetween( std::string startVertKey, std::string endVertKey )
{
	vertex* startVert = findVertex( startVertKey );
	vertex* endVert = findVertex(endVertKey );

	if ( startVert != nullptr && endVert != nullptr )
	{
		startVert->visited = true;
		startVert->distance = 0;

		std::queue< vertex* > vertexQ; // Queue because it imitates a BFS
		vertexQ.push( startVert );

		while( vertexQ.size() != 0 )
		{
			vertex* curV = vertexQ.front(); // Like peek
			vertexQ.pop(); // Removes top without returning it
			for (int i = 0; curV->adjacent.size(); ++i)
			{
				if ( !curV->adjacent[ i ].v->visited )
				{
					curV->adjacent[ i ].v->distance = curV->distance+1; // This counts the number of hops
					if ( curV->adjacent[ i ].v->key == endVertKey )
					{
						return curV->adjacent[ i ].v->distance;
					}
					else
					{
						curV->adjacent[ i ].v->visited = true;
						vertexQ.push( curV->adjacent[ i ].v );
					}
				}
			}
		}
	}
	else
	{
		if ( startVert == nullptr )
		{
			std::cout << "Error: vertex " << startVert->key << " does not exist" << std::endl;
		}
		if ( endVert == nullptr )
		{
			std::cout << "Error: vertex " << endVert->key << " does not exist" << std::endl;
		}
		return -1;
	}
	// If there is no connection
	std::cout << "No connection between " << startVertKey << " and " << endVertKey << std::endl;
	return -1;
}

void Graph::BFPath( std::string startVertKey, std::string endVertKey)
{
	vertex* startVert = findVertex( startVertKey );
	vertex* endVert = findVertex( endVertKey );
	bool pathComplete = false;

	if ( startVert != nullptr && endVert != nullptr )
	{
		startVert->visited = true;
		startVert->distance = 0;
		startVert->parent = nullptr;
		std::queue< vertex* > vertexQ;
		vertexQ.push( startVert );
		while( vertexQ.size() != 0 && !pathComplete )
		{
			vertex* curV = vertexQ.front();
			vertexQ.pop();
			for (int i = 0; i < curV->adjacent.size(); ++i)
			{
				if ( !curV->adjacent[ i ].v->visited )
				{
					curV->adjacent[ i ].v->distance = curV->distance + 1;
					curV->adjacent[ i ].v->parent = curV;
					if ( curV->adjacent[ i ].v->key == endVertKey )
					{
						pathComplete = true; // Breaks while loop
						break; // Breaks for loop
					}
					else
					{
						curV->adjacent[ i ].v->visited = true;
						vertexQ.push( curV->adjacent[ i ].v );
					}
				}
			}
		}
	if ( pathComplete ) // Rewrite in reverse order to push things to stack
	{
		int hopCount = 0;
		std::cout << "Moving backwards, beginning at: " << endVertKey << std::endl;
		vertex* curParent = endVert->parent;
		while ( curParent != nullptr )
		{
			hopCount++;
			std::cout << "Next hop: " << curParent->key << std::endl;
			std::cout << "Hop Count: " << hopCount << std::endl;
			curParent = curParent->parent;
		}
		std::cout << "Path complete" << std::endl;
	}
	else
	{
		std::cout << "No path between " << startVertKey << " and " << endVertKey << std::endl;
	}
	}
	else // If start or end is nullptr
	{
		std::cout << "Error: either start or end is nullptr" << std::endl;
	}
}

// NOTE: This implementation assumes there is a path between startVertKey and endVertKey

void Graph::dijkstra( std::string startVertKey, std::string endVertKey )
{
	vertex* startVert = findVertex( startVertKey );
	vertex* endVert = findVertex( endVertKey );
	int curDist;
	int minDistance; // Shortest path while looking at vertices
	vertex* solvedVertex; // Has the shortest path
	vertex* curV; // Current Vertex while searching
	vertex* curParent;

	if( startVert != nullptr && endVert != nullptr )
	{
		startVert->solved = true;
		startVert->distance = 0;
		std::vector< vertex* > solvedVertices;
		solvedVertices.push_back( startVert );
		while ( !endVert->solved ) // Keeping going until end vertex is solved; If there is no path to endVert, that is a problem--infinite loop
		{
			minDistance = INT_MAX; // Nothing will be greater than INT_MAX; Guaranteed other number is smaller
			// solvedVertex = nullptr; // For error-checking
			for ( int i = 0; i < solvedVertices.size(); ++i )
			{
				curV = solvedVertices[ i ]; // curV = start; only if solved
				for (int j = 0; j < curV->adjacent.size() ; ++j)
				{
					if ( !curV->adjacent[ j ].v->solved )
					{
						curDist = curV->distance + curV->adjacent[ j ].weight; // curV->distance = the sum of the path
						if ( curDist < minDistance )
						{
							solvedVertex = curV->adjacent[ j ].v; // solvedVertex = currently solved vertex
							minDistance = curDist;
							curParent = curV;
						}
					}
				}
			}
			// if ( solvedVertex ) // If you reach the end without solving the vertex, there is no path
			// {
			// 	/* code */
			// }
			solvedVertex->distance = minDistance;
			solvedVertex->parent = curParent;
			solvedVertex->solved = true; // Now, it is solved
			solvedVertices.push_back( solvedVertex );
		}
		// if ( endVert )
		// {
		// 	/* code */
		// }
		std::cout << "Shortest path from " << startVertKey << " to " << endVertKey << " is " << endVert->distance << std::endl;
	}
	else
	{
		// Handle error cases here
	}
}

int main()
{
	Graph myGraph;
	myGraph.insertVertex("South Boulder");
	myGraph.insertVertex("Glacier Ice Cream");
	myGraph.insertVertex("Golden");
	myGraph.insertVertex("Superior");
	myGraph.insertVertex("Superior Costco");
	myGraph.insertVertex("Wildwood Guitars");
	myGraph.insertVertex("Denver");
	myGraph.insertVertex("Rep Fitness");
	myGraph.insertVertex("IKEA");

	myGraph.insertEdge("South Boulder", "Glacier Ice Cream", 1);
	myGraph.insertEdge("Glacier Ice Cream", "South Boulder", 1);
	myGraph.insertEdge("South Boulder", "Superior", 5);
	myGraph.insertEdge("South Boulder", "Golden", 15);
	myGraph.insertEdge("Golden", "South Boulder", 15);
	myGraph.insertEdge("Superior", "Superior Costco", 1);
	myGraph.insertEdge("Superior", "South Boulder", 5);
	myGraph.insertEdge("Superior Costco", "Superior", 1);
	myGraph.insertEdge("Superior", "Wildwood Guitars", 1);
	myGraph.insertEdge("Superior", "Denver", 10);
	myGraph.insertEdge("Denver", "Superior", 10);
	myGraph.insertEdge("Denver", "Golden", 15);
	myGraph.insertEdge("Denver", "Rep Fitness", 3);
	myGraph.insertEdge("Denver", "IKEA", 20);

	// cout << "BFT Starting at South Boulder" << endl;
	// myGraph.BFTraversal("South Boulder");

	// std::cout << "BFT Starting at Denver" << std::endl;
	// myGraph.BFTraversal("Denver");
	int numHops;
	numHops = myGraph.BFTdistanceBetween( "South Boulder", "IKEA" );
	if ( numHops != -1 )
	{
		std::cout << "Number of hops between South Boulder and IKEA: " << numHops << std::endl;
	}
	myGraph.resetGraph();

}

// Non-recursive DFS uses a stack, BFS uses a queue
// Between recursive and non-recursive, DFS output will be different
