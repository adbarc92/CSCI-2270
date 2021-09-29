#include <iostream>

struct Node 
{
	int ID = -1;
	Node* left = nullptr;
	Node* right = nullptr;
	Node* parent = nullptr;
};

class BST // Binary search tree
{
private:
	Node* root = nullptr;
	Node* createNode(int, Node*, Node*, Node*);
	int getSize(Node*); // Private because nothing public returns root
public:
	BST();
	~BST(); // will need to delete all nodes
	bool addNode(int); // return false when full or node already exists
	bool deleteNode(int); // returns false when you can't find the node
	bool findSmallestNode(int&);
	bool findLargestNode(int&);
	int getSizeTree();
};

BST::BST(){}

BST::~BST()
{

}

Node* BST::createNode(int itemToAdd, Node* parentNode, Node* leftChild, Node* rightChild)
{
	Node* newNode = new Node; // Allocate space in heap
	newNode->ID = itemToAdd;
	newNode->right = rightChild;
	newNode->left = leftChild;
	newNode->parent = parentNode;

	return newNode;
}

bool BST::findLargestNode(int&)
{
	if (root != nullptr)
	{
		Node* tmpNode = root;
		while (tmpNode->right != nullptr)
		{
			tmpNode = tmpNode->right;
		}
		return tmpNode->ID;
	}
	else
	{
		std::cout << "Binary search tree does not exist" << std::endl;
		return -1;
	}
}

int BST::getSizeTree()
{
	return getSize(root); // Root is a private member, so only private members can access it; User cannot call root
}

int BST::getSize(Node* startNode)
{
	int size = 0;
	if (startNode != nullptr)
	{
		size++;
		size+=getSize(startNode->left);
		size+=getSize(startNode->right);
	}
	return size;
}

bool BST::addNode( int itemToAdd )
{
	Node* tmpNode = root;
	Node* curParent = nullptr;
	while (tmpNode != nullptr)
	{
		curParent = tmpNode;
		if (itemToAdd == tmpNode->ID)
		{
			std::cout << "Item already added" << std::endl;
			return false;
		}
		else
		{
			if ( itemToAdd < tmpNode->ID)
			{
				tmpNode = tmpNode->left;
			}
			else
				tmpNode = tmpNode->right;
		}
	}
	if (curParent == nullptr) // If empty tree
	{
		root = createNode( itemToAdd,nullptr,nullptr,nullptr );
		std::cout << "Item: " << itemToAdd << " added to root" << std::endl;
	}
	else if (itemToAdd < curParent->ID)
	{
		curParent->left = createNode(itemToAdd,curParent,nullptr,nullptr);
		std::cout << "Item: " << itemToAdd << " added to left of " << curParent->ID << std::endl;
	}
	else
	{
		curParent->right = createNode(itemToAdd,curParent,nullptr,nullptr);
		std::cout << "Item: " << itemToAdd << " added to right of " << curParent->ID << std::endl;
	}
	return true;
}