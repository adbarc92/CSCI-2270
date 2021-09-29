#include <iostream>

// Exam 2

// Password: fryday

//================================================================
//=========================M/C====================================
//================================================================

// Question 1: If I consider the root as level 0, what is the maximum number of nodes at level i of a BST?
	// Answer: 2^i

// Question 2: For the following array of integers, build a BST. What does the final tree look like?
	// Array: [4, 65, 23, 34, 1, 32, 100, 2]
	// Answer: See Screenshot

// Question 3: What variable stores the number of arguments to a program?
	// Answer: argc

// Question 4: If X is a node added to a red-black tree, then initially x.color = ?
	// Answer: red

// Question 5: Suppose we run Dijkstra’s shortest-path algorithm on the above weighted graph with vertex A as the source and H . In what order do the nodes get included into the set of vertices for which the shortest path is found? Note, start your answer with A and put a single space between each vertex. Your answer should be in all capital letters.
	// A C D B E G F H (11)

//================================================================
//=======================Programming==============================
//================================================================

// Question 1: Write a function that replaces the maximum node value in a BST with the minimum node value in a BST, and then deletes the minimum node. This will not produce a valid BST

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

		else if ( !min->rightChild && !min->rightChild )
		{
			if ( min->key > min->parent->key )
			{
				min->parent->rightChild = nullptr;
				delete min;
			}
			else
			{
				min->parent->leftChild = nullptr;
				delete min;
			}
		}
	}
}

// Question 2: Write a C++ function to check if a path exists between two vertices in an unweighted graph that is less than a given value. The function takes three paramters: source vertex, destination vertex, and distance integer. It should return true if there is a path between the two vertices that is less than "dist." Otherwise, return false

bool Graph::ifPathExistsLessThanDist( std::string vertex1, std::string vertex2, int dist )
{
	if ( vertex1 != vertex2 )
	{
		vertex* startVert;
		vertex* endVert;

		int i = 0;
		while ( i < vertices[i].size() )
		{
			if ( vertices[ i ].name == vertex1 )
			{
				startVert = vertices[ i ];
			}
			else if ( vertices[ i ].name == vertex2 )
			{
				endVert = vertices[ i ];
			}
			i++;
		}

		int curDist = 0;

		if ( startVert && endVert )
		{
			startVert->visited = true;
			for (int i = 0; i < startVert->adj.size(); ++i)
			{
				/* code */
			}
		}
	}

}


















