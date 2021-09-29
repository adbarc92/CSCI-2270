void Graph::findNodeWithMaximumAdjacent(int startVertex) {
	vertex *start;
	for (int i = 0; i < (int)vertices.size(); i++) {
		vertices[i].visited = false;
		if (vertices[i].value == startVertex) {
			start = &vertices[i];
		}
	}

	queue<vertex*> Q;
	Q.push(start);
	unsigned int max = 0;
	int key;
	start->visited = true;
	cout << start->value << " ";
    while (!Q.empty()) {
    	vertex *node = Q.front();
    	Q.pop();
    	for (int i = 0; i < (int)node->adj.size(); i++) {
            if(!node->adj[i].v->visited)
            {
                node->adj[i].v->visited=true;
                Q.push(node->adj[i].v);
                cout<<node->adj[i].v->value<<" ";
                if(node->adj.size() > max)
                {
                    max = node->adj.size();
                    key = node->value;
                }
            }
    	}
	}
	cout<<endl<<key<<endl;
}
