#include <iostream>
using namespace std;

struct Node
{
	string item;
	Node *next;
};

Node * searchLL( Node *head, string target );

int main()
{
	string a[] = {"uno", "dos", "tres", "cuatro"};

	Node *head, *current, *tmp;
	head = new Node;
	current = new Node;


	head->item = a[0];
	head->next = nullptr;

	current = head;

	int i = 1;
	while( i < 4 )
	{
		// create new node; use tmp to point to it
		tmp = new Node;

		// populate the payload of tmp with i-th array element
		tmp->item = a[i];
		// in case it's the last element, set current node to indicate end
		tmp->next = nullptr;

		// at this point "current" is still pointing to previous element
		// (could be head)
		// connect the previous element such that it is pointing to the newly created one (tmp)
		current->next = tmp; 

		// move forward. Make current point to the new element
		current = tmp;

		i++;

	}

	Node *targetAddress = searchLL( head, "dos" );
	cout << "targetAddress " << targetAddress << endl;


	cout << "Traverse and print the LL: " << endl;
	current = head;

	while( current != nullptr )
	{
		cout << current->item << endl;
		cout << current << endl;
		current = current->next;
	}


	return 0;
}


Node * searchLL( Node *head, string target )
{
	Node *current;
	current = head;

	while( current!=nullptr )
	{
		if( current->item == target )
			return current;
		else
			current = current->next;
	}

	return nullptr;
}











