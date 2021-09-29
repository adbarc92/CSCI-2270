#include <iostream>
#include <string>

class Node
{
public:
	int payload;
	Node* next;

	Node()
	{
		payload = 0;
		next = NULL;
	}
};

class LinkedList : Node
{
public:

	bool has_payload;
	LinkedList();
	void add( int payload );
	void print ();
	void del (int payload);
	int get( int i);
};

LinkedList::LinkedList() : Node()
{
	has_payload = false;
}

void LinkedList::add( int payload )
{
	if ( !has_payload )
	{
		this->payload = payload;
		this->has_payload = true;
		return;
	}

	Node* n = new Node();
	n->payload = payload;
	Node* node = this;


	while( node->next != NULL )
	{
		node = node->next;
	}
	node->next = n;
};

void LinkedList::print()
{
	for( Node* node = this; node != NULL; node = node->next )
	{
		std::cout << "PAYLOAD: " << node->payload << std::endl;
	}
	std::cout << std::endl;
};

void LinkedList::del( int i )
{

	if( i == 0 )
	{
		if (next == NULL)
		{
			has_payload = false;
			return;
		}
		for( Node* node = this; node != NULL; node = node->next )
		{
			if (node->next != NULL) // If there's another node
			{
				node->payload = node->next->payload;
				if (node->next->next == NULL)
				{
					delete node->next;
					node->next = NULL;
					return;
				}
			}
		}
	}

	int ctr = 0;
	for( Node* node = this; node != NULL; node = node->next )
	{
		if( ctr == i - 1 )
		{
			Node* next = node->next->next;
			delete node->next;
			node->next = next;
			return;
		}
		ctr++;
	}	
}

int LinkedList::get(int i)
{
	int ctr = 0;
	for( Node* node = this; node != NULL; node = node->next )
	{
		if( ctr == i )
		{
			return node->payload;
		}
		ctr++;
	}
	throw std::runtime_error( "Index out of bounds." );	
};

int main()
{
	// Node* ll = NULL;

	// ll = ll_add( ll, 5 );
	// ll = ll_add( ll, 10 );
	// ll = ll_add( ll, 15 );
	// ll = ll_add( ll, 20 );
	// ll = ll_add( ll, 100 );
	// ll = ll_add( ll, 200 );

	// ll_print( ll );

	// int a = ll_get( 0, ll );
	// int b = ll_get( 3, ll );

	// printf( "0.) %d\n", a );
	// printf( "3.) %d\n", b );

	// ll = ll_delete( ll, 0 );
	// ll = ll_delete( ll, 3 );

	// ll_print( ll );

	LinkedList* ll = new LinkedList();
	ll->add(1);
	ll->add(2);
	ll->add(3);
	ll->del(1);
	ll->print();

	return 0;

}
