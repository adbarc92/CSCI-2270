#include <iostream>

struct Node
{
	int ID = -1;
	Node* left = nullptr;
	Node* right = nullptr;
	Node* parent = nullptr;
};

class BST
{
	private:
		Node* root = nullptr;
		Node* createNode(int, Node*, Node*, Node* ); // Done
		int getSize(Node*);
		bool addNodeRPriv( Node*, int ); // Private because it accesses Node
		Node* search( Node*, int );
	public:
		BST();
		~BST();
		bool addNode(int);
		bool deleteNode(int);
		bool findSmallestNode(int&);
		bool findLargestNode(int&);
		int getSizeOfTree(); // Done

		bool addNodeR(int);
		bool searchPub( int );
};

int BST::getSizeOfTree()
{
	return getSize( root );
}

int BST::getSize( Node* startNode )
{
	int size = 0;
	if ( startNode != nullptr )
	{
		size++;
		size+=getSize(startNode->left);
		size+=getSize(startNode->right);
	}
	return size;
}

BST::BST(){}

BST::~BST(){}

bool searchPub( int )
{

}

Node* search( Node*, int )
{

}

Node* BST::createNode( int itemToAdd, Node* parentNode, Node* leftChild, Node* rightChild)
{
	Node* newNode = new Node;
	newNode->ID = itemToAdd;
	newNode->parent = parentNode;
	newNode->right = rightChild;
	newNode->left = leftChild;
}

bool BST::findLargestNode(int&)
{
	if (root != nullptr)
	{
		Node* tmpNode = root;
		while(tmpNode->right != nullptr)
		{
			tmpNode = tmpNode->right;
		}
	}
	else
	{
		return -1;
	}
}

bool BST::addNode(int itemToAdd)
{
	Node* tmpNode = root;
	Node* curParent = nullptr;

	while (tmpNode != nullptr)
	{
		curParent = tmpNode;
		if (itemToAdd == tmpNode->ID)
		{
			std::cout << "Item is already in tree" << std::endl;
			return false;
		}
		else
		{
			if (itemToAdd < tmpNode->ID)
			{
				tmpNode = tmpNode->left;
			}
			else
			{
				tmpNode = tmpNode->right;
			}
		}
	}
	if ( curParent == nullptr ) // If root
	{
		root = createNode( itemToAdd, nullptr, nullptr, nullptr );
		std::cout << "Item " << itemToAdd << " added as root " << std::endl;
	}
	else if (itemToAdd < curParent->ID)
	{
		curParent->left = createNode( itemToAdd, nullptr, nullptr, nullptr );
		std::cout << "Item " << itemToAdd << " added to left of " << curParent->ID << std::endl;
	}
	else
	{
		curParent->right = createNode( itemToAdd, nullptr, nullptr, nullptr );
		std::cout << "Item " << itemToAdd << " added to right of " << curParent->ID << std::endl;
	}
}

bool BST::addNodeR( int itemToAdd )
{
	if ( root == nullptr )
	{
		Node* newNode = createNode( itemToAdd, nullptr, nullptr, nullptr );
		root = newNode;
		std::cout << "Item " << itemToAdd << " added as root" << std::endl;
		return true;
	}
	else
	{
		return addNodeRPriv( root, itemToAdd );
	}
}

bool BST::addNodeRPriv( Node* curNode, int itemToAdd ) // This cannot be called from main; This method will also work for searching
{
	// Keep moving down
	if (itemToAdd < curNode->ID)
	{
		if ( curNode->left != nullptr )
		{
			return addNodeRPriv( curNode->left, itemToAdd );
		}
		else
		{
			curNode->left = createNode( itemToAdd, curNode, nullptr, nullptr );
			std::cout << "Item " << itemToAdd << " added to the left of " << curNode->ID << std::endl;
			return true;
		}
	}
	else if ( itemToAdd > curNode->ID )
	{
		if ( curNode->right != nullptr )
		{
			return addNodeRPriv( curNode->right, itemToAdd );
		}
		else
		{
			curNode->right = createNode( itemToAdd, curNode, nullptr, nullptr );
			std::cout << "Item " << itemToAdd << " added to the right of " << curNode->ID << std::endl;
			return true;
		}
	}
	else
	{
		std::cout << "Item " << itemToAdd << " already in tree" <<std::endl;
		return false;
	}
}

Node* BST::search( Node* startNode, int itemToFind )
{
	if ( startNode != nullptr )
	{
		if ( itemToFind < startNode->ID && startNode->left != nullptr ) // Item DNE
		{
			return search( startNode->left, itemToFind );
		}
		else if ( itemToFind > startNode->ID && startNode->right != nullptr )
		{
			return search( startNode->right, itemToFind );
		}
		else if ( itemToFind == startNode->ID )
		{
			return startNode;
		}
		else // Should never happen
		{
			std::cout << "Value " << itemToFind << " not found" << std::endl;
		}
	}
	return startNode;
}

int main()
{
	BST niceTree;
	niceTree.addNode(17);

	return 0;
}