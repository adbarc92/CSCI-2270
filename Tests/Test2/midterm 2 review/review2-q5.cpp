Node *temp = new Node;
Node *nextTemp = new Node;
Node *a = new Node;
bool found = false;
void inTraversal(TreeNode *root, char m, char n)
{
		if(root)
		{
		    inTraversal(root->left, m, n);
			if(found)
			{
			    nextTemp = new Node;
			    nextTemp -> key = root ->key;
			    temp -> next = nextTemp;
			    temp = temp->next;
			} 
			if(root->key == m && !head)
			{
			    a -> key = root -> key;
			    head = a;
			    temp = head;
			    found = true;
			}
			if(root -> key == n)
			{
			    temp->next = NULL;
			    return;
			}
			inTraversal(root->right, m, n);
		}
}

void RangeSearch(TreeNode *node, char m, char n)
{
    inTraversal(node,m,n);
    
}