#include "MovieTree.hpp"

#include <iostream>

//return true if 'a' should come before 'b', false otherwise
bool should_be_first( MovieNodeLL* a, MovieNodeLL* b )
{
	int cmp = a->title.compare( b->title );
	if( cmp == -1 )
	{
		return true;
	}
	else
	{
		return false;
	}
}

MovieNodeLL* ll_add( MovieNodeLL* head, int ranking, std::string title, int year, int quantity )
{
	MovieNodeLL* ret = new MovieNodeLL( ranking, title, year, quantity );
	if( !head )
	{
		return ret;
	}

	if( !head->next )
	{
		if( should_be_first( ret, head ) )
		{
			ret->next = head;
			return ret;
		}
		else
		{
			head->next = ret;
			return head;
		}
	}

	if( should_be_first( ret, head ) )
	{
		ret->next = head;
		return ret;
	}

	MovieNodeLL* prev = head;
	for( MovieNodeLL* node = head; node != nullptr; node = node->next )
	{
		if( should_be_first( ret, node ) )
		{
			ret->next = node;
			prev->next = ret;
			return head;
		}
		prev = node;
	}

	ret->next = nullptr;
	prev->next = ret;
	return head;
}

// Unsorted version of ll_add
// MovieNodeLL* ll_add( MovieNodeLL* head, int ranking, std::string title, int year, int quantity )
// {
// 	MovieNodeLL* ret = new MovieNodeLL( ranking, title, year, quantity );
// 	if( !head )
// 	{
// 		return ret;
// 	}

// 	MovieNodeLL* prev = head;
// 	for( MovieNodeLL* node = head; node != nullptr; node++ )
// 	{
// 		prev = node;
// 	}

// 	ret->next = nullptr;
// 	prev->next = ret;
// 	return head;
// }

MovieNodeLL* ll_remove( MovieNodeLL* head, std::string title )
{
	if( head )
	{
		if( head->title == title )
		{
			MovieNodeLL* ret = head->next;
			delete head;
			return ret;
		}

		MovieNodeLL* prev = head;
		for( MovieNodeLL* node = head; node != nullptr; node = node->next )
		{
			if( node->title == title )
			{
				prev->next = node->next;
				delete node;
				return head;
			}
			prev = node;	
		}
	}
	return nullptr;
}

void ll_remove_all( MovieNodeLL* head )
{
	if( head )
	{
		std::cout << "Deleting: " << head->title << std::endl;
		for( MovieNodeLL* node = head; node->next != nullptr; node = node->next )
		{
			std::cout << "Deleting: " << node->next->title << std::endl;
			delete node->next;
		}
		delete head;
	}
}

MovieNodeLL* ll_get( MovieNodeLL* head, std::string title )
{
	if( head )
	{
		for( MovieNodeLL* node = head; node != nullptr; node = node->next )
		{
			if( node->title == title )
			{
				return node;
			}	
		}
	}
	return nullptr;
}

int ll_size( MovieNodeLL* head )
{
	int ret = 0;
	if( head )
	{
		for( MovieNodeLL* node = head; node != nullptr; node = node->next )
		{
			ret++;	
		}
	}
	return ret;
}

void ll_print( MovieNodeLL* head )
{
	if( head )
	{
		for( MovieNodeLL* node = head; node != nullptr; node = node->next )
		{
			std::cout << "Movie: " << node->title << " " << node->quantity << std::endl; 	
		}
	}
}

MovieTree::MovieTree()
{
	root = nullptr;
}

MovieTree::~MovieTree()
{
	DeleteAll( root );
}

void MovieTree::printMovieInventory()
{
	printMovieInventory( root );
}

void MovieTree::printMovieInventory( MovieNodeBST* node )
{
	if( node )
	{
		printMovieInventory( node->leftChild );
		ll_print( node->head );
		printMovieInventory( node->rightChild );
	}
}

int MovieTree::countMovieNodes()
{
	int count = 0;
	countMovieNodes( root, &count );
	return count;
}

void MovieTree::countMovieNodes( MovieNodeBST* node, int* c )
{
	if( node )
	{
		countMovieNodes( node->leftChild, c );
		*c += ll_size( node->head );
		countMovieNodes( node->rightChild, c );
	}
}

void MovieTree::deleteMovieNode( std::string title )
{
	MovieNodeBST* node = searchBST( root, title );
	if( node )
	{
		node->head = ll_remove( node->head, title );
		if( node->head )
		{
			return;
		}

		MovieNodeBST* parent = node->parent;

		if( node->leftChild && node->rightChild )
		{
			MovieNodeBST* leftmost_node = treeMinimum( node->rightChild );
			node->letter = leftmost_node->letter;
			node->head = leftmost_node->head;

			MovieNodeBST* leftmost_parent = leftmost_node->parent;
			if( leftmost_parent->leftChild == leftmost_node )
			{
				leftmost_parent->leftChild = nullptr;
			}
			else
			{
				leftmost_parent->rightChild = nullptr;
			}

			node = leftmost_node;
		} 
		else
		{
			// if both leftChild and rightChild are nullptr, replace_node will be nullptr
			MovieNodeBST* replace_node = node->leftChild ? node->leftChild : node->rightChild;
			if( replace_node )
			{
				replace_node->parent = parent;
			}

			if( parent )
			{
				if( parent->rightChild == node )
				{
					parent->rightChild = replace_node;
				}
				else
				{
					parent->leftChild = replace_node;
				}
			}
			else
			{
				root = replace_node;
			}
		}

		delete node;
	}
	else
	{
		std::cout << "Movie not found." << std::endl;
	}
}

void MovieTree::addMovieNode( int ranking, std::string title, int releaseYear, int quantity )
{
	if( !root )
	{
		MovieNodeBST* bstnode = new MovieNodeBST( title[ 0 ] );
		root = bstnode;
		return;
	}

	//select parent node of the new node
	MovieNodeBST* node = root;
	while( node )
	{
		MovieNodeBST* node2 = ( title[ 0 ] < node->letter ? node->leftChild : node->rightChild );
		if( !node2 )
		{
			break;
		}
		if( node2->letter == title[ 0 ] )
		{
			node2->head = ll_add( node2->head, ranking, title, releaseYear, quantity );
			return;
		}
		else
		{
			node = node2;
		}
	}

	MovieNodeBST* bstnode = new MovieNodeBST( title[ 0 ] );
	bstnode->head = ll_add( bstnode->head, ranking, title, releaseYear, quantity );

	if( title[ 0 ] < node->letter )
	{
		node->leftChild = bstnode;
		bstnode->parent = node;
	}
	else
	{
		node->rightChild = bstnode;
		bstnode->parent = node;
	}
}

void MovieTree::findMovie( std::string title )
{
	MovieNodeBST* bstnode = searchBST( root, title );
	if( bstnode )
	{
		MovieNodeLL* llnode = searchLL( bstnode->head, title );
		std::cout << "Movie info:" << std::endl;
		std::cout << "===========" << std::endl;
		std::cout << "Ranking: " << llnode->ranking << std::endl;
		std::cout << "Title: " << llnode->title << std::endl;
		std::cout << "Year: " << llnode->year << std::endl;
		std::cout << "Quantity: " << llnode->quantity << std::endl;
	}
	else
	{
		std::cout << "Movie not found." << std::endl; 
	}
}

void MovieTree::rentMovie( std::string title )
{
	MovieNodeBST* bstnode = searchBST( root, title );
	if( bstnode )
	{
		MovieNodeLL* llnode = searchLL( bstnode->head, title );
		llnode->quantity--;
		std::cout << "Movie has been rented." << std::endl;
		findMovie( title );
		if( llnode->quantity <= 0 )
		{		
			deleteMovieNode( title );
		}
	}
	else
	{
		std::cout << "Movie not found." << std::endl; 
	}	
}

MovieNodeBST* MovieTree::searchBST( MovieNodeBST* node, std::string title )
{
	if( node && node->letter == title[ 0 ] )
	{
		if( searchLL( node->head, title ) )
		{
			return node;
		}
		else
		{
			return nullptr;
		}
	}
	else if( node )
	{
		MovieNodeBST* n = searchBST( node->leftChild, title );
		if( !n )
		{
			n = searchBST( node->rightChild, title );
		}
		else
		{
		}
		return n;
	}
	else
	{
		return nullptr;
	}
}

MovieNodeLL* MovieTree::searchLL( MovieNodeLL* head, std::string title )
{
	return ll_get( head, title );
}

void MovieTree::DeleteAll( MovieNodeBST* node )
{
	if( node == root )
	{
		root = nullptr;
	}
	if( node )
	{
		MovieNodeBST* tmp = node->leftChild;
		DeleteAll( node->rightChild );
		ll_remove_all( node->head );
		delete node;
		DeleteAll( tmp );
	}
}

MovieNodeBST* MovieTree::treeMinimum( MovieNodeBST *node )
{
	MovieNodeBST* ret = node;
	while( ret->leftChild != nullptr )
	{
		ret = ret->leftChild;
	}
	return ret;
}
