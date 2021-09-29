#include <iostream>
#include "Lab5doublyLL.h"

doublyLL::doublyLL() {

}

doublyLL::doublyLL(int nodeID) {
	//create head node
	head = createNode(nodeID, nullptr, nullptr);
	tail = head;
}

doublyLL::~doublyLL() {

}


Node* doublyLL::createNode(int key, Node* next, Node* previous)
{
	Node* newNode = new Node;
	newNode->key = key;
	newNode->next = next;
	newNode->previous = previous;
	return newNode;
}

bool doublyLL::insertNodeAtEnd(int key)
{
	Node* newNode = createNode(key, nullptr, nullptr);
	if (head == nullptr)
	{
		head = newNode;
		tail = head;
	}
	else
	{
		Node* currentNode = head;
		while (currentNode->next != nullptr )
		{
			currentNode = currentNode->next;
		}
		currentNode->next = newNode;
		tail = newNode;
	}
	return true;
}

bool doublyLL::deleteNode(int key)
{
	for (Node* currentNode = head; currentNode != nullptr; currentNode = currentNode->next)
	{
		if (currentNode->key == key)
		{
			if (currentNode->next == nullptr && currentNode->previous == nullptr) // If
			{
				delete currentNode;
				head = nullptr;
				tail = nullptr;
				return true;
			}
			if (currentNode->next == nullptr)
			{
				currentNode->previous->next = nullptr;
				tail = currentNode->previous;
				delete currentNode;
				return true;
			}
			if (currentNode->previous == nullptr) // If head
			{
				currentNode->next->previous = nullptr;
				head = currentNode->next;
				delete currentNode;
				return true;
			}
			currentNode->previous->next = currentNode->next;
			currentNode->next->previous = currentNode->previous;
			delete currentNode;
			return true;
		}
	}	
	std::cout << "There are no nodes matching this value" << std::endl;
	return false;
}

void doublyLL::print_list()
{
	
	for (Node* currentNode = head; currentNode != nullptr; currentNode = currentNode->next)
	{
		std::cout << "Current node is: " << currentNode->key << std::endl;
	}
}