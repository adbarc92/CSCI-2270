void Graph::findVerticesWithNoAdjacentVertices()
{   
    queue<vertex*> Q;
    bool found = false;
    for(int i=0; (int) i<vertices.size();i++)
    {
        if(vertices[i].adj.size() == 0)
        {
            found = true;
            cout<<vertices[i].name<<" ";
        }
    }
    if(!found)
    {
        cout<<"Not Found!"<<endl;
    }
}