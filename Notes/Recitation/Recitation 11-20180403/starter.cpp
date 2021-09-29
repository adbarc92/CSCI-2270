#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

struct vertex;

struct adjVertex {
	vertex* v;
	int weight;
};

struct vertex {
	string key;
	vector<adjVertex> adjacent;
	bool visited = false;
};

class Graph {
	private:
		//vertices
		vector<vertex> vertices;
		vertex* findVertex(string);
	public:
		//methods for accessing graphs
		Graph();
		~Graph();
		void insertVertex(string);	//identifier of the vertex
		void insertEdge(string,string,int);	//start, end, weight
		void printGraph();
		void Graph::DFSpath(string, string);
		void Graph::findNodeWithMaximumAdjacent(string);

};

Graph::Graph() {}

Graph::~Graph() {}

void Graph::insertVertex(string value) {
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
		cout << "There is already a vertex " << value << " in this graph" << endl;
	}
}

vertex* Graph::findVertex(string value) {
	int i=0;
	while (i<vertices.size()) {
		if (vertices[i].key == value) {
			return &vertices[i];
		}
		i++;
	}
	return nullptr;
}



void Graph::insertEdge(string v1, string v2, int weight) {
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
			cout << "no vertex with name " << v1 << " in this graph" << endl;
		}
		if (vEnd == nullptr) {
			cout << "no vertex with name " << v2 << " in this graph" << endl;
		}
	}
}

void Graph::findNodeWithMaximumAdjacent(string start) {

	vertex* startVert = findVertex( start );
	if ( startVert != nullptr )
	{

		bool pathComplete = false;
		int adjConnections = 0;
		int curMax = 0;
		vertex* maxAdj = startVert;
		std::queue< vertex* > vertexQ;
		vertexQ.push( maxAdj );
		
		while ( vertexQ.size() != 0 && !pathComplete )
		{
			vertex* curV = vertexQ.front();
			vertexQ.pop();			
			for (int i = 0; i < curV->adjacent.size(); ++i)
			{
				adjConnections++;
				if ( !curV->adjacent[ i ].v->visited )
				{
					curV->adjacent[ i ].v->visited = true;
					vertexQ.push( curV->adjacent[ i ].v );
				}
			}
			if ( adjConnections > curMax )
			{
				curMax = adjConnections;
				maxAdj = curV;
			}
		}
		for (int i = 0; i < vertexQ.size(); ++i)
		{
			std::cout << vertexQ.front() << " ";
			vertexQ.pop();
		}

		std::cout << maxAdj->key << std::endl;
	}
}


void Graph::DFSpath(string src, string dst) {

	vertex* startVert = findVertex( src );
	vertex* endVert = findVertex( dst );

	std::stack< vertex* > vertexStack;
	vertexStack.push( startVert );
	
	for (int i = 0; i < startVert->adjacent.size(); ++i)
	{
		vertex* currentVertex = startVert->adjacent[ i ].v;
		vertexStack.push( currentVertex );
		if ( currentVertex == endVert )
		{
			break;
		}
	}
	while ( vertexStack.size() != 0 )
	{
		std::cout << vertexStack.top() << " --> ";
		vertexStack.pop();
	}

}



int main() {

	Graph myGraph;

	myGraph.insertVertex("A");
	myGraph.insertVertex("B");
	myGraph.insertVertex("C");
	myGraph.insertVertex("D");
	myGraph.insertVertex("E");
	myGraph.insertVertex("F");
	myGraph.insertVertex("G");

	myGraph.insertEdge("A", "B", 0); myGraph.insertEdge("B", "A", 0);
	myGraph.insertEdge("A", "C", 0); myGraph.insertEdge("C", "A", 0);
	myGraph.insertEdge("B", "D", 0); myGraph.insertEdge("D", "B", 0);
	myGraph.insertEdge("C", "D", 0); myGraph.insertEdge("D", "C", 0);
	myGraph.insertEdge("E", "D", 0); myGraph.insertEdge("D", "E", 0);
	myGraph.insertEdge("E", "B", 0); myGraph.insertEdge("B", "E", 0);
	myGraph.insertEdge("E", "G", 0); myGraph.insertEdge("G", "E", 0);
	myGraph.insertEdge("F", "G", 0); myGraph.insertEdge("G", "F", 0);




	


}