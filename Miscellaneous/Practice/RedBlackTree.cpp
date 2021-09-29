#include <iostream>
#include <iomanip>

#include "RedBlackTree.hpp"

RedBlackTree::RedBlackTree()
{
	root = nullptr;
}

RedBlackTree::~RedBlackTree()
{
	deleteTree( root );
}

void RedBlackTree::insertNode( int value )
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

NodeRBT* RedBlackTree::search( int value )
{
	return searchRB( value );
}

void RedBlackTree::deleteTree( NodeRBT* node )
{
		if ( node )
	{
		deleteTree( node->leftChild );
		deleteTree( node->rightChild );
		delete node;
	}
}

void RedBlackTree::visualizeTree()
{
	visualizeTree( root, 0 );
}



void RedBlackTree::leftRotate( int value ) // Argument: fulcrum
{
	NodeRBT* node = search( value );
	if ( node )
	{
		if ( node->rightChild )
		{
			NodeRBT* rotationPoint = node->rightChild;
			node->rightChild = rotationPoint->leftChild;
			if ( rotationPoint->leftChild != nullptr )
			{
				rotationPoint->leftChild->parent = node;
			}
			rotationPoint->parent = node->parent;
			if ( node->parent == nullptr )
			{
				root = rotationPoint;
			}
			else
			{
				node->parent->rightChild = rotationPoint;
			}
			rotationPoint->leftChild = node;
			node->parent = rotationPoint;
		}
		std::cout << "No point around which to rotate" << std::endl;
		return;
	}
	else
	{
		std::cout << "Input node does not exist" << std::endl;
	}
}

// 1. Change first node pointer from second node to second node's opposite child
// 2. If opposite child exists, set its parent to first node
// 3. Set second node's parent to first node's parent
// 4. If first node is root, second node is now root; otherwise, first node's parent's relevant (check) child to second node
// 5. Set first node's same-direction child to second node
// 6. Set second node's parent to first node

void RedBlackTree::rightRotate( int value )
{
	NodeRBT* node = search( value );
	if ( node )
	{
		if ( node->leftChild )
		{
			NodeRBT* rotationPoint = node->rightChild;
			rotationPoint->leftChild = node->rightChild;
			if ( rotationPoint->leftChild )
			{
				rotationPoint->leftChild->parent = node;
			}
			rotationPoint->parent = node->parent;
			if ( node->parent != nullptr )
			{
				root = rotationPoint;
			}
			else if ( node->parent->leftChild == node)
			{
				node->parent->leftChild = rotationPoint;
			}
			else
			{
				node->parent->rightChild = rotationPoint;
			}

			rotationPoint->rightChild = node;
			node->parent = rotationPoint;
		
		}
		else
		{
			std::cout << "No point around which to rotate" << std::endl;
			return;
		}
	}
	else
		std::cout << "Input node does not exist" << std::endl;
}

void RedBlackTree::insertRB( int value ){}

NodeRBT* RedBlackTree::searchRB( int value )
{
	NodeRBT* curNode = root;
	while ( curNode != nullptr )
	{
		if ( value > curNode->key )
		{
			curNode = curNode->rightChild;
		}
		else if ( value < curNode->key )
		{
			curNode = curNode->leftChild;
		}
		else
			return curNode;
	}
	std::cout << "No match found" << std::endl;
	return nullptr;

}

void RedBlackTree::balanceRB( NodeRBT* node ){}

void RedBlackTree::printAll( NodeRBT* node ){}

void RedBlackTree::visualizeTree( NodeRBT* node, int indent_level )
{
	if ( node )
	{
		for (int i = 0; i < indent_level; ++i)
		{
			std::cout << " ";
		}
		
		std::cout << "Key: " << node->key << " Color: " << node->color << std::endl;
		visualizeTree( node->leftChild, indent_level+4 );
		visualizeTree( node->rightChild, indent_level+4 );
	}
}

NodeRBT* RedBlackTree::findMinimum( NodeRBT* node )
{
	return nullptr;
}



void test()
{
	RedBlackTree rb;

	rb.insertNode( 5 );
	rb.insertNode( 6 );
	rb.insertNode( 3 );
	rb.insertNode( 2 );
	rb.insertNode( 10 );
	rb.insertNode( 1 );
	rb.insertNode( 15 );
	rb.insertNode( 7 );
	rb.insertNode( 8 );
	rb.insertNode( 4 );

	rb.visualizeTree();

	rb.leftRotate( 3 );
	rb.visualizeTree();
}