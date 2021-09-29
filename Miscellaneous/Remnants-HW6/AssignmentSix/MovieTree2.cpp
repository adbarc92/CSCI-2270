#include <iostream>
#include "MovieTree.hpp"

MovieTree::MovieTree(){
	root = nullptr;
};

MovieTree::~MovieTree(){
	DeleteAll(root);
}

MovieNodeLL* LL_add( MovieNodeLL* head, int in_ranking, std::string in_title, int in_year, int in_quantity )
{
	if ( head == nullptr )
	{
		MovieNodeLL* ret = new MovieNodeLL(in_ranking,in_title,in_year,in_quantity);
		return ret;
	}
	MovieNodeLL* newMovie = new MovieNodeLL(in_ranking,in_title,in_year,in_quantity);
	MovieNodeLL* currentNode = head;
	while(currentNode->next != nullptr)
	{
		currentNode = currentNode -> next;
	}
	currentNode->next = newMovie;
	return head;
}

void LL_print( MovieNodeLL* head )
{
	if (head != nullptr)
	{
		for (MovieNodeLL* currentNode = head; currentNode != nullptr; currentNode = currentNode->next)
		{
			std::cout << "Movie: " << currentNode->title << " " << currentNode->quantity << std::endl;
		}
	}
	else
		std::cout << "No movies exist" << std::endl;
}

MovieNodeLL* LL_get(MovieNodeLL* head, std::string title) // Works
{
	if ( head )
	{
		for ( MovieNodeLL* currentNode = head; currentNode != nullptr; currentNode = currentNode->next )
		{
			if ( currentNode->title == title )
			{
				return currentNode;
			}
			
		}
		std::cout << "No match found, returning nullptr" << std::endl;
		return nullptr;
	}
	
	else
	{
		std::cout << "No LL exists, returning nullptr" << std::endl;
		return nullptr;
	}
}

MovieNodeLL* LL_remove( MovieNodeLL* head, std::string title ) // Works
{
	if ( head )
	{
		MovieNodeLL* tmpNode;
		
		if ( head->title == title ) // If removing head
		{
			tmpNode = head->next;
			delete head;
			return tmpNode;
		}

		for ( MovieNodeLL* currentNode = head; currentNode->next != nullptr; currentNode = currentNode->next )
		{
			if ( currentNode->next->title == title )
			{
				tmpNode = currentNode->next;
				currentNode->next = currentNode->next->next;
				delete tmpNode;
				tmpNode = currentNode;
				return head;
			}
		}
		return nullptr;
	}
	else
	{
		std::cout << "No head exists, returning nullptr" << std::endl;
		return nullptr;
	}
}

int LL_get_size( MovieNodeLL* head )
{
	if ( head != nullptr )
	{
		int size = 1;
		for (MovieNodeLL* currentNode = head; currentNode != nullptr; currentNode = currentNode->next )
		{
			if ( currentNode->next )
			{
				size++;
			}
		}
		return size;
	}
	else
		std::cout << "No list exists" << std::endl;
	return 0;
}

MovieNodeLL* LL_remove_all( MovieNodeLL* head ) // Works
{
	MovieNodeLL* currentNode = head;
	MovieNodeLL* tmpNode;
	while ( currentNode != nullptr )
	{
		tmpNode = currentNode->next;
		delete currentNode;
		currentNode = tmpNode;
	}
	head = nullptr;
	return head;
}

void MovieTree::addMovieNode( int ranking, std::string title, int releaseYear, int quantity )
{
	MovieNodeBST* currentNode = root;
	while ( currentNode )
	{
		if ( title[0] > currentNode->letter && currentNode->rightChild != nullptr )
		{
			currentNode = currentNode->rightChild;
		}
		else if ( title[0] < currentNode->letter && currentNode->leftChild != nullptr  )
		{
			currentNode = currentNode->leftChild;
		}
		else if ( title[0] == currentNode->letter )
		{
			if ( searchLL( currentNode->head, title ) == nullptr )
			{
				currentNode->head = LL_add( currentNode->head, ranking, title, releaseYear, quantity );
				return;
			}
			else
			{
				std::cout << "Item exists" << std::endl;
				return;
			}
		}
		else
			break;
	}

	MovieNodeBST* newNode = new MovieNodeBST( title[0] );
	newNode->head = LL_add( newNode->head, ranking, title, releaseYear, quantity );

	if( !root )
	{
		root = newNode;
		return;
	}

	newNode->parent = currentNode;
	if ( newNode->letter < currentNode->letter )
	{
		currentNode->leftChild = newNode;
	}
	else if ( newNode->letter > currentNode->letter )
	{
		currentNode->rightChild = newNode;
	}
}

void MovieTree::printMovieInventory()
{
	printMovieInventory( root );
	
}

int MovieTree::countMovieNodes()
{
	int c = 0;
	int* cRef = &c;
	countMovieNodes( root, cRef );
	return c;
}

void MovieTree::deleteMovieNode( std::string title )
{
	MovieNodeBST* currentNodeBST = searchBST( root, title );
	if ( currentNodeBST != nullptr )
	{
		currentNodeBST->head = LL_remove( currentNodeBST->head, title );


		if( currentNodeBST->head )
		{
			return;
		}

		if( currentNodeBST->leftChild && currentNodeBST->rightChild )
		{
			MovieNodeBST* minimum = treeMinimum( currentNodeBST->rightChild );
			currentNodeBST->letter = minimum->letter;
			currentNodeBST->head = minimum->head;

			if( minimum->parent->leftChild == minimum )
			{
				minimum->parent->leftChild = nullptr;
			}
			else
			{
				minimum->parent->rightChild = nullptr;
			}

			delete minimum;		
		}
		else if( currentNodeBST->leftChild || currentNodeBST->rightChild )
		{
			MovieNodeBST* replaceNode = currentNodeBST->leftChild;
			if( !replaceNode )
			{
				replaceNode = currentNodeBST->rightChild;
			}

			replaceNode->parent = currentNodeBST->parent;

			if( currentNodeBST->parent )
			{
				if( currentNodeBST->parent->leftChild == currentNodeBST )
				{
					currentNodeBST->parent->leftChild = replaceNode;
				}
				else
				{
					currentNodeBST->parent->rightChild = replaceNode;
				}
			}

			if( currentNodeBST == root )
			{
				root = replaceNode;
			}
			delete currentNodeBST;
		}
		else
		{
			if( currentNodeBST->parent )
			{
				if( currentNodeBST->parent->leftChild == currentNodeBST )
				{
					currentNodeBST->parent->leftChild = nullptr;
				}
				else
				{
					currentNodeBST->parent->rightChild = nullptr;
				}
			}
			if( currentNodeBST == root )
			{
				root = nullptr;
			}		
			delete currentNodeBST;
		}
	}
}

void MovieTree::findMovie( std::string title )
{
	MovieNodeBST* node = searchBST( root, title );
	
	if ( !node )
	{
		std::cout << "Movie not found." << std::endl;
		return;
	}

	MovieNodeLL* foundMovie = searchLL( node->head, title );

	if ( foundMovie )
	{
		std::cout << "Movie Info:" << std::endl;
		std::cout << "===========" << std::endl;
		std::cout << "Ranking:" << foundMovie->ranking << std::endl;
		std::cout << "Title:" << foundMovie->title << std::endl;
		std::cout << "Year:" << foundMovie->year << std::endl;
		std::cout << "Quantity:" << foundMovie->quantity << std::endl;
	}
	else
	{
		std::cout << "Movie not found." << std::endl;
		return;
	}
}

void MovieTree::rentMovie( std:: string title )
{
	MovieNodeBST* node = searchBST( root, title );
	
	if ( !node )
	{
		std::cout << "Movie not found." << std::endl;
		return;
	}
		
	MovieNodeLL* foundMovie = searchLL( node->head, title );

	if ( foundMovie )
	{
		foundMovie->quantity--;
		std::cout << "Movie has been rented." << std::endl;
		std::cout << "Movie Info:" << std::endl;
		std::cout << "===========" << std::endl;
		std::cout << "Ranking:" << foundMovie->ranking << std::endl;
		std::cout << "Title:" << foundMovie->title << std::endl;
		std::cout << "Year:" << foundMovie->year << std::endl;
		std::cout << "Quantity:" << foundMovie->quantity << std::endl;
		if ( foundMovie->quantity == 0 )
		{
			deleteMovieNode ( title );
		}
	}
	else
	{
		std::cout << "Movie not found." << std::endl;
		return;
	}
}

void MovieTree::DeleteAll(MovieNodeBST * node) //use this for the post-order traversal deletion of the tree
{
	if ( node )
	{
		DeleteAll( node->rightChild );
		DeleteAll( node->leftChild );

		delete node;
	}
}

void MovieTree::printMovieInventory(MovieNodeBST * node)
{
	if ( node )
	{
		printMovieInventory( node->leftChild );
		LL_print( node->head );
		printMovieInventory( node->rightChild );
	}
}

void MovieTree::countMovieNodes(MovieNodeBST *node, int *c)
{
	if ( node )
	{
		int size = 1;
		if ( node->head != nullptr )
		{
			
			for (MovieNodeLL* currentNode = node->head; currentNode != nullptr; currentNode = currentNode->next )
				{
					if ( currentNode->next )
					{
						size++;
					}
				}
		}
		else
		{
		std::cout << "No list exists" << std::endl;
		return;
		}
		*c = *c + size;
		countMovieNodes( node->rightChild, c );
		countMovieNodes( node->leftChild, c );
	}
}

MovieNodeBST* MovieTree::searchBST( MovieNodeBST *node, std::string title ) //use this recursive function to find a pointer to a node in the BST, given a MOVIE TITLE
{
	if ( node != nullptr )
	{
		if ( title[0] < node->letter )
		{
			return searchBST( node->leftChild, title );
		}
		else if ( title[0] > node->letter )
		{
			return searchBST( node->rightChild, title );
		}
		else if ( title[0] == node->letter )
			return searchLL( node->head, title) ? node : nullptr;
		else // Match not found
			return nullptr;
	}
	else
		return nullptr;
}

MovieNodeLL* MovieTree::searchLL(MovieNodeLL* head, std::string title)
{
	return LL_get( head, title );
}

MovieNodeBST* MovieTree::treeMinimum(MovieNodeBST *node) //use this to find the left most leaf node of the BST, you'll need this in the delete function
{
	while ( node->leftChild )
	{
		node = node->leftChild;
	}
	return node;
}

void testBST( )
{
	MovieTree mt;

	mt.addMovieNode( 10, "D", 1995, 5 );
	mt.addMovieNode( 10, "B", 1995, 6 );
	mt.addMovieNode( 10, "A", 1995, 88 );
	mt.addMovieNode( 10, "C", 1995, 10 );
	mt.addMovieNode( 10, "F", 1995, 1 );
	mt.addMovieNode( 10, "E", 1995, 1 );
	mt.addMovieNode( 10, "S", 1995, 1 );
	mt.addMovieNode( 10, "M", 1995, 1 );
	mt.addMovieNode( 10, "X", 1995, 1 );
	mt.printMovieInventory();

	mt.findMovie("X");
	mt.rentMovie("M");
	mt.findMovie("M");
}

void testLL( )
{
	MovieTree rentalLibrary;

	MovieNodeLL* head = nullptr;
	head = LL_add( head, 1, "A movie", 1995, 10 );
	head = LL_add( head , 3, "C movie", 1992, 8);
	head = LL_add( head, 2, "B movie", 1994, 9 );
	head = LL_add( head, 2, "D movie", 1994, 9 );
	head = LL_add( head, 2, "E movie", 1994, 9 );
	LL_print( head );
	std::cout << std::endl;

	head = LL_remove( head, "A movie" );
	LL_print( head );
	std::cout << std::endl;
	head = LL_remove( head, "E movie" );
	LL_print( head );
	std::cout << std::endl;
	head = LL_remove( head, "B movie" );
	LL_print( head );
	std::cout << std::endl;

	// int size = LL_get_size( head );
	// std::cout << "Size: " << size << std::endl;
	// LL_print( head );
	// head = LL_remove_all( head );

	// LL_print( head );
}