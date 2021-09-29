#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

struct vertex;

struct adjVertex{
    vertex *v;
    int weight;
};

struct vertex{
    std::string name;
    std::vector<adjVertex> adj;
};

class Graph
{
    public:
        Graph();
        ~Graph();
        void addEdge(std::string v1, std::string v2, int weight);
        void addVertex(std::string name);
        void displayEdges();
    protected:
    private:
        //vector<edge> edges;
        std::vector<vertex> vertices;

};

//------------------------------------------------------------------------------------

Graph::Graph()
{

}

Graph::~Graph()
{
    //dtor
}
void Graph::addEdge( std::string v1, std::string v2, int weight){

    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == v1){
            for(int j = 0; j < vertices.size(); j++){
                if(vertices[j].name == v2 && i != j){
                    adjVertex av;
                    av.v = &vertices[j];
                    av.weight = weight;
                    vertices[i].adj.push_back(av);
                    //another vertex for edge in other direction
                    /*adjVertex av2;
                    av2.v = &vertices[i];
                    av2.weight = weight;
                    vertices[j].adj.push_back(av2);*/
                }
            }
        }
    }
}
void Graph::addVertex( std::string n ){
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == n){
            found = true;
            std::cout << vertices[i].name << " found." << std::endl;
        }
    }
    if(found == false){
        vertex v;
        v.name = n;
        vertices.push_back(v);

    }
}

void Graph::displayEdges(){
    //loop through all vertices and adjacent vertices
    for(int i = 0; i < vertices.size(); i++){
        std::cout<<vertices[i].name<<"-->";
        for(int j = 0; j < vertices[i].adj.size(); j++){
            std::cout<<vertices[i].adj[j].v->name<<"("<<vertices[i].adj[j].weight<<")"<<"***";
        }
        std::cout<<std::endl;
    }
}


//------------------------------------------------------------------------------------

bool load_graph( std::string filename, Graph& g )
{
	std::fstream fs;
	std::stringstream ss;
	fs.open( filename );

	if( !fs )
	{
		std::cout << "Cannot graph file: " << filename << std::endl;
		return false;
	}

	std::vector< std::string > cities;

	std::string city_name_list;
	std::getline( fs, city_name_list );

	ss.str( city_name_list );
	std::string city_name;
	std::getline( ss, city_name, ' ' ); //the first city is 'dest/source' which isn't a city name
	while( std::getline( ss, city_name, ' ' ) )
	{
		cities.push_back( city_name );
		g.addVertex( city_name );
	}

	std::string line;
	while( std::getline( fs, line ) )
	{
		ss.clear();
		ss.str( line );
		std::string city_name = "";
		std::getline( ss, city_name, ' ' ); //the first column is the name of the city
		std::string weight_str;
		int i = 0;
		while( std::getline( ss, weight_str, ' ' ) )
		{
			int weight = std::stoi( weight_str );
			if( weight > 0 )
			{
				std::cout << "ADD EDGE " << city_name << " " << cities[ i ] << " " << weight << std::endl;
				g.addEdge( city_name, cities[ i ], weight );
			}
			i++;
		}
	}

	return true;
}

int main() {
	Graph g;
	load_graph( "mat.txt", g );
	g.displayEdges();
	return 0;
}