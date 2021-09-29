#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct vertex;

struct adjVertex{
    vertex *v;
};

struct vertex{
    std::string name;
    bool visited;
    int distance;
    std::vector<adjVertex> adj;
};

class Graph
{
    public:
        Graph();
        ~Graph();
        void addEdge(std::string v1, std::string v2);
        void addVertex(std::string name);
	bool ifPathExistsLessThanDist(string vertex1, string vertex2, int dist);
    protected:
    private:
        std::vector<vertex> vertices;

};

Graph::Graph()
{

}

Graph::~Graph()
{
    //dtor
}
void Graph::addEdge(string v1, string v2){

    for(int i = 0; i < (int)vertices.size(); i++){
        if(vertices[i].name == v1){
            for(int j = 0; j < (int)vertices.size(); j++){
                if(vertices[j].name == v2 && i != j){
                    adjVertex av;
                    av.v = &vertices[j];
                    vertices[i].adj.push_back(av);
                    //another vertex for edge in other direction
                    adjVertex av2;
                    av2.v = &vertices[i];
                    vertices[j].adj.push_back(av2);
                }
            }
        }
    }
}
void Graph::addVertex(string n){
    bool found = false;
    for(int i = 0; i < (int)vertices.size(); i++){
        if(vertices[i].name == n){
            found = true;
            //cout<<vertices[i].name<<" found."<<endl;
        }
    }
    if(found == false){
        vertex v;
        v.name = n;
		v.visited = false;
        vertices.push_back(v);

    }
}

bool Graph::ifPathExistsLessThanDist( std::string vertex1, std::string vertex2, int dist )
{
    if ( vertex1 != vertex2 )
    {
        vertex* startVert;
        vertex* endVert;

        int i = 0;
        while ( i < int(vertices.size()) )
        {
            if ( vertices[ i ].name == vertex1 )
            {
                startVert = &vertices[ i ];
            }
            else if ( vertices[ i ].name == vertex2 )
            {
                endVert = &vertices[ i ];
            }
            i++;
        }

        if ( startVert && endVert )
        {
            vertex* curV;
            for (int i = 0; i < int( startVert->adj.size() ); ++i)
            {
                if ( startVert->adj[i].v->name == vertex2 )
                {
                    if ( 1 < dist )
                    {
                        return true;
                    }
                    else
                        return false;

                }
               curV = startVert->adj[i].v;
               for (int j = 0; j < int( curV->adj.size() ); ++j)
               {
                   if ( curV->adj[j].v->name == vertex2 )
                   {
                       if ( 2 < dist )
                       {
                           return true;
                       }
                       else
                        return false;
                   }
               }
            }

            
        }
    }
    return false;
}



int main() {
    Graph g;

    g.addVertex("a");
    g.addVertex("b");
    g.addVertex("c");
    g.addVertex("d");
    g.addVertex("e");

    g.addEdge("a", "b");
    g.addEdge("a", "d");
    g.addEdge("c", "d");
    g.addEdge("b", "c");
    g.addEdge("d", "e");
    g.addEdge("c", "e");

    cout << g.ifPathExistsLessThanDist("c", "b", 1) << endl;;

    return 0;
}