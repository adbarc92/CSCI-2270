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

        int curDist = 0;

        if ( startVert && endVert )
        {
            for (int i = 0; i < int(startVert->adj.size()); ++i)
            {
                curDist++;
                if ( startVert->adj[i].v->name == vertex2 )
                {
                    if ( curDist <  dist )
                    {
                        return true;
                    }
                    else
                        return false;
                }
            }
        }
    }
    return false;
}