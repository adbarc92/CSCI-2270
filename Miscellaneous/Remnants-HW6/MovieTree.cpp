#include <iostream>
#include "MovieTree.hpp"

MovieTree::MovieTree(){
	root = nullptr;
};

MovieTree::~MovieTree(){
	DeleteAll(root);
}

bool should_come_before( std::string A, std::string B )
{
	if ( A.compare(B) < 0 )
	{
		return true;
	}
	else
	{
		return false;
	}
}

MovieNodeLL* LL_add( MovieNodeLL* head, int in_ranking, std::string in_title, int in_year, int in_quantity )
{
	if ( head == nullptr )
	{
		MovieNodeLL* ret = new MovieNodeLL( in_ranking, in_title, in_year, in_quantity );
		return ret;
	}
	
	MovieNodeLL* newMovie = new MovieNodeLL( in_ranking, in_title, in_year, in_quantity );
	
	if ( should_come_before( in_title, head->title ))
	{

		newMovie->next = head;
		return newMovie;
	}

	MovieNodeLL* prev = head;
	
	for (MovieNodeLL* currentNode = head; currentNode != nullptr; currentNode = currentNode->next )
	{
		if ( should_come_before( in_title, currentNode->title ) )
		{
			break;
		}
		prev = currentNode;
	}
	newMovie->next = prev->next;
	prev->next = newMovie;
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
		return nullptr;
	}
	
	else
	{
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
		std::cout << "Deleting: " << currentNode->title << std::endl;
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
		if( !searchLL( currentNodeBST->head, title ) )
		{
			std::cout << "Movie not found." << std::endl;
			return;
		}

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

	   if( minimum->rightChild )
	   {
	    currentNodeBST->rightChild = minimum->rightChild;
	   }

	   if( minimum->parent != currentNodeBST )
	   {
	    if( minimum->parent->leftChild == minimum )
	    {
	     minimum->parent->leftChild = nullptr;
	    }
	    else
	    {
	     minimum->parent->rightChild = nullptr;
	    }
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
	else
	{
		std::cout << "Movie not found." << std::endl;
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
		DeleteAll( node->leftChild );
		DeleteAll( node->rightChild );
		node->head = LL_remove_all( node->head );
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

	// mt.addMovieNode( 10, "A", 1995, 5 );
	// mt.addMovieNode( 10, "B", 1995, 6 );
	// mt.addMovieNode( 10, "S", 1995, 88 );
	// mt.addMovieNode( 10, "T", 1995, 88 );
	// mt.addMovieNode( 10, "W", 1995, 88 );

	// mt.deleteMovieNode( "S" );

	// mt.printMovieInventory();

	// std::cout << "====" << std::endl;

	// mt.deleteMovieNode( "S1" );
	// mt.deleteMovieNode( "S2" );
	// mt.deleteMovieNode( "S3" );
	// mt.deleteMovieNode( "S" );

	// mt.printMovieInventory();

	// std::cout << "====" << std::endl;

	mt.addMovieNode( 10, "Shawshank Redemption", 1995, 1 );
	mt.addMovieNode( 10, "The Godfather", 1995, 1 );
	mt.addMovieNode( 10, "The Godfather: Part II", 1995, 1 );
	mt.addMovieNode( 10, "The Dark Knight", 1995, 1 );
	mt.addMovieNode( 10, "Pulp Fiction", 1995, 1 );
	mt.addMovieNode( 10, "12 Angry Men", 1995, 1 );
	mt.addMovieNode( 10, "Schindler's List", 1995, 1 );
	mt.addMovieNode( 10, "The Good the Bad and the Ugly", 1995, 1 );
	mt.addMovieNode( 10, "The Lord of the Rings: The Return of the King", 1995, 1 );
	mt.addMovieNode( 10, "Fight Club", 1995, 1 );
	mt.addMovieNode( 10, "The Lord of the Rings: The Fellowship of the Ring", 1995, 1 );
	mt.addMovieNode( 10, "Star Wars: Episode V - The Empire Strikes Back", 1995, 1 );
	mt.addMovieNode( 10, "Forrest Gump", 1995, 1 );
	mt.addMovieNode( 10, "Inception", 1995, 1 );
	mt.addMovieNode( 10, "One Flew Over the Cuckoo's Nest", 1995, 1 );
	mt.addMovieNode( 10, "The Lord of the Rings: The Two Towers", 1995, 1 );
	mt.addMovieNode( 10, "Goodfellas", 1995, 1 );
	mt.addMovieNode( 10, "The Matrix", 1995, 1 );
	mt.addMovieNode( 10, "Star Wars: Episode IV - A New Hope", 1995, 1 );
	mt.addMovieNode( 10, "Seven Samurai", 1995, 1 );
	mt.addMovieNode( 10, "Interstellar", 1995, 1 );
	mt.addMovieNode( 10, "City of God", 1995, 1 );
	mt.addMovieNode( 10, "Se7en", 1995, 1 );
	mt.addMovieNode( 10, "The Usual Suspects", 1995, 1 );
	mt.addMovieNode( 10, "The Silence of the Lambs", 1995, 1 );
	mt.addMovieNode( 10, "It's a Wonderful Life", 1995, 1 );
	mt.addMovieNode( 10, "Once Upon a Time in the West", 1995, 1 );
	mt.addMovieNode( 10, "Leon: The Professional", 1995, 1 );
	mt.addMovieNode( 10, "Life Is Beautiful", 1995, 1 );
	mt.addMovieNode( 10, "Casablanca", 1995, 1 );
	mt.addMovieNode( 10, "Raiders of the Lost Ark", 1995, 1 );
	mt.addMovieNode( 10, "American History X", 1995, 1 );
	mt.addMovieNode( 10, "Saving Private Ryan", 1995, 1 );
	mt.addMovieNode( 10, "City Lights", 1995, 1 );
	mt.addMovieNode( 10, "Spirited Away", 1995, 1 );
	mt.addMovieNode( 10, "Psycho", 1995, 1 );
	mt.addMovieNode( 10, "Rear Window", 1995, 1 );
	mt.addMovieNode( 10, "Whiplash", 1995, 1 );
	mt.addMovieNode( 10, "Whiplash", 1995, 1 );
	mt.addMovieNode( 10, "The Untouchables", 1995, 1 );
	mt.addMovieNode( 10, "Modern Times", 1995, 1 );
	mt.addMovieNode( 10, "Terminator 2: Judgment Day", 1995, 1 );
	mt.addMovieNode( 10, "Memento", 1995, 1 );
	mt.addMovieNode( 10, "The Green Mile", 1995, 1 );
	mt.addMovieNode( 10, "The Pianist", 1995, 1 );
	mt.addMovieNode( 10, "The Departed", 1995, 1 );
	mt.addMovieNode( 10, "Apocalypse Now", 1995, 1 );
	mt.addMovieNode( 10, "Sunset Blvd.", 1995, 1 );
	mt.addMovieNode( 10, "Gladiator", 1995, 1 );
	mt.addMovieNode( 10, "Dr. Strangelove or: How I Learned to Stop Worrying and Love the Bomb", 1995, 1 );
	mt.addMovieNode( 10, "Back to the Future", 1995, 1 );

	mt.deleteMovieNode( "Saving Private Ryan" );
	mt.deleteMovieNode( "Schindler's List" );
	mt.deleteMovieNode( "Se7en" );
	mt.deleteMovieNode( "Seven Samurai" );
	mt.deleteMovieNode( "Shawshank Redemption" );
	mt.deleteMovieNode( "Spirited Away" );
	mt.deleteMovieNode( "Star Wars: Episode IV - A New Hope" );
	mt.deleteMovieNode( "Star Wars: Episode V - The Empire Strikes Back" );
	mt.deleteMovieNode( "Sunset Blvd." );

	// mt.deleteMovieNode( )

	mt.printMovieInventory();

	// mt.findMovie("X");
	// mt.rentMovie("M");
	// mt.findMovie("M");
}

void testLL( )
{
	MovieTree rentalLibrary;

	MovieNodeLL* head = nullptr;
	head = LL_add( head, 1, "The Big Bad Elbow", 1995, 10 );
	head = LL_add( head , 3, "Tickle Me Elmo", 1992, 8);
	head = LL_add( head, 2, "Try Hards in Gym Class", 1994, 9 );
	// head = LL_add( head, 2, "D movie", 1994, 9 );
	// head = LL_add( head, 2, "E movie", 1994, 9 );
	LL_print( head );
	std::cout << std::endl;

	// head = LL_remove( head, "A movie" );
	// LL_print( head );
	// std::cout << std::endl;
	// head = LL_remove( head, "E movie" );
	// LL_print( head );
	// std::cout << std::endl;
	// head = LL_remove( head, "B movie" );
	// LL_print( head );
	// std::cout << std::endl;

	// int size = LL_get_size( head );
	// std::cout << "Size: " << size << std::endl;
	// LL_print( head );
	// head = LL_remove_all( head );

	// LL_print( head );
}