#include <iostream>
#include <vector>
#include <queue>
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
		void BFTraversal(string);	//start node
};

Graph::Graph() {

}

Graph::~Graph() {
	
}

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

void Graph::BFTraversal(string vertName) {
	queue<vertex*> vertexQ;
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
					cout << "just visited " << curV->adjacent[i].v->key << endl;
					vertexQ.push(curV->adjacent[i].v);
				}
			}
		}
	}
	else {
		cout << "vertex " << vertName << " not in graph" << endl;
	}
}



int main() {
/*
	vector<int> vectorOfInts;
	cout << "size of vectorOfInts " << vectorOfInts.size() << endl;
	vectorOfInts.push_back(5);
	cout << "size of vectorOfInts " << vectorOfInts.size() << endl;
	vectorOfInts.push_back(10);
	cout << "size of vectorOfInts " << vectorOfInts.size() << endl;
	vectorOfInts.push_back(15);
	cout << "size of vectorOfInts " << vectorOfInts.size() << endl;

	for (int i=0; i<vectorOfInts.size(); i++) {
		cout << "item " << i << " is " << vectorOfInts[i] << endl;
	}
*/
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

	cout << "BFT Starting at Denver" << endl;
	myGraph.BFTraversal("Denver");



}