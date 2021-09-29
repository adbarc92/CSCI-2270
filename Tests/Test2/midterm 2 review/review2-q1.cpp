void Graph::shortestPath(string source, string destination, string intermediate)
{
    unsigned int k=0;
    vertex* src;
    vertex* dest;
    queue<vertex*> vQ;
    while (k<vertices.size()) {
        if (vertices[k].name == source) {
            src = &vertices[k];
            break;
        }
        k++;
    }
    
    if(src)
    {
        src->visited = true;
        src->prev = NULL;
        bool found = false;
        vQ.push(src);
        while(vQ.size() != 0 && !found)
        {
            vertex* curV = vQ.front();
            vQ.pop();
            for(unsigned int i=0; i<curV->adj.size(); i++)
            {
                count++;
                if(!curV->adj[i].v->visited)
                {
                    curV->adj[i].v->visited = true;
                    curV->adj[i].v->prev = curV;
                    vQ.push(curV->adj[i].v);
                    if(curV->adj[i].v->name == destination)
                    {
                        dest = curV->adj[i].v;
                        found = true;
                        break;
                    }
                }
            }
            if(found)
            {
                break;
            }
        }
        vertex* temp = dest;
        found = false;
        while(temp)
        {
            if(temp -> name == intermediate)
            {
                cout<<"Yes"<<endl;
                found = true;
                break;
            }
            temp = temp->prev;
        }
        if(!found)
        {
            cout<<"No"<<endl;
        }
    }
    
}