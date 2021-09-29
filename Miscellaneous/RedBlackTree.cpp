#include <iostream>
#include <iomanip>

#include "RedBlackTree.hpp"

RedBlackTree::RedBlackTree()
{
	root = nullptr;
}

RedBlackTree::~RedBlackTree()
{
	deleteTree();
}

void RedBlackTree::insertRB( int value )
{
	NodeRBT* newNode = new NodeRBT( value );
	if ( !root )
	{
		root = newNode;
		return;
	}
	
	NodeRBT* currentNode = root;
	NodeRBT* parentNode;
	
	while (currentNode != nullptr )
	{
		parentNode = currentNode;
		currentNode = ( value > currentNode->key ? currentNode->rightChild : currentNode->leftChild );
	}
	
	currentNode = newNode;
	newNode->parent = parentNode;
	
	if ( newNode->key > parentNode->key )
	{
		parentNode->rightChild = newNode;
	}
	else
	{
		parentNode->leftChild = newNode;
	}
	return;
}

NodeRBT* RedBlackTree::insertRB2( NodeRBT *pt )
{
    /* If the tree is empty, return a new node */
    if (root == NULL)
       return pt;
 
    /* Otherwise, recur down the tree */
    if (pt->data < root->data)
    {
        root->left  = BSTInsert(root->left, pt);
        root->left->parent = root;
    }
    else if (pt->data > root->data)
    {
        root->right = BSTInsert(root->right, pt);
        root->right->parent = root;
    }
 
    /* return the (unchanged) node pointer */
    return root;
}

void RedBlackTree::leftRotate( NodeRBT* node ){}

void RedBlackTree::visualizeTree()
{
	visualizeTree( root, 0 );
}

void RedBlackTree::visualizeTree( NodeRBT* node, int indent_level )
{
	if ( node )
	{
		for (int i = 0; i < indent_level; ++i)
		{
			std::cout << " ";
		}
		
		std::cout << "Node key: " << node->key << " Node Color: " << node->color << std::endl;
		visualizeTree( node->leftChild, indent_level+4 );
		visualizeTree( node->rightChild, indent_level+4 );
	}
}

void test()
{
	RedBlackTree rb;

	rb.insertNode( 5 );
	rb.insertNode( 6 );
	rb.insertNode( 3 );
	rb.insertNode( 2 );
	rb.insertNode( 10 );

	rb.visualizeTree();
}