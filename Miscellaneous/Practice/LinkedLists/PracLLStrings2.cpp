#include <iostream>
#include <string>

class Node
{
	public:
		std::string payload;
		Node* next;

		Node()
		{
			payload = "Payload";
			next = NULL;
		}
};

class LinkedList : Node // Object
{
public:
	bool has_payload;
	LinkedList ();
	void add ( std::string payload );
	void print ( );
	void del ( int i ) ;
	std::string get ( int i );
};

LinkedList::LinkedList () : Node () // Constructor
{
	has_payload = false;
}

void LinkedList::add ( std::string payload )
{
	if ( !has_payload)
	{
		this->payload = payload;
		this->has_payload = true;
		return;
	}

	Node* n = new Node (); // Pointers - n vs. node...?
	n->payload = payload;
	Node* node = this;

	while ( node->next != NULL ) // Confusing
	{
		node = node->next;
	}
	node->next = n;
}; // Why does this need a semi-colon?

void LinkedList::print ( )
{
	for (Node* node = this; node != NULL; node = node->next) // Also confusing
	{
		std::cout << "The string is: " << node->payload << std::endl;
	}
	std::cout << std::endl;
};

void LinkedList::del ( int i ) // Double check why this is structured as it is
{
	if ( i == 0 )
	{
		if ( next == NULL )
		{
			has_payload = false;
			return;
		}
		for ( Node* node = this; node != NULL; node = node->next )
		{
			if ( node->next != NULL ) // If there is another node
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
	for ( Node* node = this; node != NULL; node = node->next )
	{
		if ( ctr == i - 1 )
		{
			Node* next = node->next->next;
			delete node->next;
			node->next = next;
			return;
		}
		ctr++;
	}
};

std::string LinkedList::get ( int i )
{
	int ctr = 0;
	for ( Node* node = this; node != NULL; node = node->next )
	{
		if ( ctr == i )
		{
			return node->payload;
		}
		ctr++;
	}
	throw std::runtime_error ( "Index out of bounds." );
};

int main()
{
	int x;
	std::cout << "Enter the line number: " << std::endl;
	std::cin >> x;
	LinkedList* ll = new LinkedList();
	ll->add("This is the first line.");
	ll->add("This is the second line.");
	ll->add("This is the third line.");
	ll->add("This is the fourth line.");
	std::cout << ll->get(x) << std::endl;
	x = x - 1;
	ll->del(x);
	ll->print();
	
	return 0;
}