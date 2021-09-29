#include <iostream>

struct TreeNode
{
	int key;
	TreeNode* leftChild;
	TreeNode* rightChild;
	TreeNode* parent;
};

void replaceMaxWithMin ( TreeNode* root )
{
if ( root != nullptr )
	{
		TreeNode* curNode = root;
		
		while( curNode->leftChild != nullptr )
		{
			curNode = curNode->leftChild;
		}
		
		TreeNode* min = curNode;

		curNode = root;

		while( curNode->rightChild )
		{
			curNode = curNode->rightChild;
		}

		TreeNode* max = curNode;

		max->key = min->key;

		TreeNode* curParent = min->parent;

		if ( min->rightChild )
		{
			min->key = min->rightChild->key;
			curNode = min->rightChild;
			delete curNode;
			min->rightChild = nullptr;
		}
		else if ( !min->rightChild && min->leftChild )
		{
			min->key = min->leftChild->key;
			curNode = min->leftChild;
			delete curNode;
			min->leftChild = nullptr;
		}
	}
}