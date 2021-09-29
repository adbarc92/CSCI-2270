#pragma once
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