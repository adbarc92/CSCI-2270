#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

struct Pregger
{
	std::string name;
	int priority;
	int treatment;
};

struct PreggerLL
{
	std::string name;
	int priority;
	int treatment;
	PreggerLL* next;
};

bool shouldComeBefore( std::pair< int, int>, std::pair< int, int> );

class SLinkedList
{
public:
	SLinkedList();
	SLinkedList( std::string, int, int );
	~SLinkedList();
	void insertNode( std::string, int, int );
	void deleteNode( std::string );
	bool comparePriority( PreggerLL*, PreggerLL* );
	void pubPrint();
	void dequeue();
	void enqueue( std::string, int, int );
private:
	PreggerLL* createPregger( std::string, int, int );
	PreggerLL* head = nullptr;
	void deletePreggers();
	PreggerLL* findPregger( std::string, PreggerLL* head );
	void printPreggers( PreggerLL* );
};

SLinkedList::SLinkedList(){}

SLinkedList::~SLinkedList(){
	deletePreggers();
}

// Minimum first; correct order returns true, incorrect returns false (if false, addition is placed)
bool comparePriority( PreggerLL* addition, PreggerLL* original ) // If correct order, true;
{
	if ( addition != nullptr && original == nullptr ) // If nothing to compare to
	{
		return false;
	}
	
	if ( addition->priority > original->priority )
	{
		return true;
	}
	
	else if ( addition->priority < original->priority )
	{
		return false;
	}
	
	else if ( addition->priority == original->priority )
	{
		if ( addition->treatment < original->treatment )
		{
			return false;
		}
		else
			return true;
	}
	
	else
		return true;
}

PreggerLL* SLinkedList::createPregger( std::string name, int priority, int treatment )
{
	PreggerLL* newNode = new PreggerLL;
	newNode->name = name;
	newNode->priority = priority;
	newNode->treatment = treatment;
	newNode->next = nullptr;

	return newNode;
}

void SLinkedList::deletePreggers()
{
	for ( PreggerLL* currentNode = head; currentNode->next != nullptr; )
	{
		PreggerLL* tmpNode = currentNode;
		currentNode = currentNode->next;
		delete tmpNode;
	}
}

void SLinkedList::deleteNode( std::string name )
{
	for ( PreggerLL* currentNode = head; currentNode->next != nullptr; currentNode = currentNode->next )
	{
		if ( currentNode->next->name == name )
		{
			currentNode->next = currentNode->next->next;
			currentNode = currentNode->next;
			delete currentNode;
		}
	}
}

void SLinkedList::insertNode( std::string name, int priority, int treatment )
{
	PreggerLL* newNode = createPregger( head, name, priority, treatment );
	if ( !head )
	{
		head = newNode;
	}
	
	else // Head node exists
	{
		for ( PreggerLL* currentNode = head ; currentNode->next != nullptr ; currentNode = currentNode->next )
		{
			// If head->priority >= newNode->priority
				// If head->priority == newNode->priority
					// If head->treatment > newNode->treatment
			// If currentNode->next->priority >= newNode->priority
				// If currentNode->next->priority == newNode->priority
					// If currentNode->next->treatment > newNode->treatment
			// If currentNode->next == nullptr;
				// currentNode->next = newNode;
				// newNode->next = nullptr;
			if ( !comparePriority( newNode, currentNode ) && currentNode == head )
			{
				newNode->next = currentNode;
				head = newNode;
			}

			if ( !comparePriority( newNode, currentNode->next ) ) // If newNode should go before currentNode->next
			{
				newNode->next = currentNode->next;
				currentNode->next = newNode;
			}
		}
	}
}

PreggerLL* SLinkedList::findPregger( std::string name, PreggerLL* next )
{
	if ( !head )
	{
		std::cout << "No list" << std::endl;
		return nullptr;
	}

	for ( PreggerLL* currentNode = head; currentNode != nullptr ; currentNode = currentNode->next )
	{
		if ( currentNode->name == name )
		{
			return currentNode;
		}
	}

	std::cout << "No matching Pregger" << std::endl;
	return nullptr;
}

void SLinkedList::printPreggers( PreggerLL* head )
{
	for ( PreggerLL* currentNode = head; currentNode->next != nullptr; currentNode = currentNode->next )
	{
		std::cout << "Name: " << currentNode->name << ", Priority: " << currentNode->priority << ", Treatment: " << currentNode->treatment << std::endl;
	}
}

void SLinkedList::pubPrint()
{
	printPreggers( head );
}