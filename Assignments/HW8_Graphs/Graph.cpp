#include <iostream>
#include <vector>

#include "Graph.h"

Graph::Graph(){}

Graph::~Graph(){}

void Graph::addEdge( std::string v1, std::string v2, int distance ) // Works
{
	for ( int i = 0; i < vertices.size(); ++i )
	{
		if ( vertices[i].name == v1 )
		{
			for ( int j = 0; j < vertices.size(); ++j )
			{
				if ( vertices[j].name == v2 && i != j )
				{
					adjVertex newVertex;
					newVertex.v = &vertices[ j ];
					newVertex.weight = distance;
					vertices[ i ].adj.push_back( newVertex );
				}
			}
		}
	}
}

void Graph::addVertex(std::string name) // Works
{
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == name){
            found = true;
            std::cout<<vertices[i].name<<" already in the graph."<<std::endl;
        }
    }
    if(found == false){
        vertex v;
        v.name = name;
        vertices.push_back(v);

    }
}

int Graph::isAdjacent( std::string v1, std::string v2 ) // Works
{
	for ( unsigned int i = 0; i < vertices.size(); ++i )
	{
		vertex& v = vertices[i];
		if ( v.name == v1 )
		{
			for ( unsigned int j = 0; j < v.adj.size(); ++j )
			{
				std::string name = v.adj[j].v->name;
				if ( name == v2 )
				{
					return 1;
				}
			}
			return 0;
		}
	}
	return 0;
}

void Graph::displayEdges()
{
    //loop through all vertices and adjacent vertices
    for(int i = 0; i < vertices.size(); i++){
        std::cout <<vertices[i].name << "-->";
        for(int j = 0; j < vertices[i].adj.size(); j++){
        	std::cout<< (j == 0 ? "" : "***")  << vertices[i].adj[j].v->name;
        }
        std::cout<<std::endl;
    }
}