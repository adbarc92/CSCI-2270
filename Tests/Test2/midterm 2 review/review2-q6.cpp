Node *newNode = new Node(NULL,NULL,NULL);
string child;
Node* insert(Node* node, int value)
{
    newNode -> key = value;
    if (node == NULL)
    {
        cout<<"inserted: "<< newNode->key <<" "<<child<<" child of: "<<newNode->parent->key<<endl;
        return newNode;
    }
    if (value < node->key)
    {   
        newNode->parent = node;
        child = "left";
        node->left  = insert(node->left, value);
    }
    else if (value > node->key)
    {
        child = "right";
        newNode->parent = node;
        node->right = insert(node->right, value); 
    }
    return newNode;
}