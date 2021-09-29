void Graph::colorVertices(string sourceVertex)
{
    vertex *start;
	for (int i = 0; i < (int)vertices.size(); i++) {
		vertices[i].visited = false;
		if (vertices[i].name == sourceVertex) {
			start = &vertices[i];
		}
	}

	queue<vertex*> Q;
	Q.push(start);
	start->visited = true;
	start->color="Red";
	while (!Q.empty()) {
		vertex* curV = Q.front();
		Q.pop();
		for(int i=0; (int) i<curV->adj.size(); i++)
		{
			if(!curV->adj[i].v->visited)
			{
				curV->adj[i].v->visited = true;
				Q.push(curV->adj[i].v);
				if(curV->color == "Red")
				{
				    curV->adj[i].v->color = "Black";
				}
				else
				{
				    curV->adj[i].v->color = "Red";
				}
			}
		}
	}	
}