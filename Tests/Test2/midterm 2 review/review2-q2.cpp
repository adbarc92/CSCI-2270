void Graph::printMislabeledParents(int startVertex) {
	vertex *start;
	for (int i = 0; i < (int)vertices.size(); i++) {
		vertices[i].visited = false;
		if (vertices[i].value == startVertex) {
			start = &vertices[i];
		}
	}

	queue<vertex*> Q;
	Q.push(start);
	start->visited = true;
	cout << start->value << endl;
	while (!Q.empty()) 
	{
		vertex* curV = Q.front();
		Q.pop();
		for(unsigned int i=0; i<curV->adj.size(); i++)
		{
			if(!curV->adj[i].v->visited)
			{
				curV->adj[i].v->visited = true;
				Q.push(curV->adj[i].v);
				if(curV->adj[i].v->parentID!=curV->value)
				{
				    cout<<curV->adj[i].v->value <<endl;
				}
			}
		}
	}	
}