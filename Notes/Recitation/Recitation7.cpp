#include <iostream>
#include "BST.cpp"


int main()
{
	BST newTree(10);
	newTree.printTree();
	std::cout << std::endl;
	newTree.insertNode(8);
	newTree.printTree();
	std::cout << std::endl;
	newTree.searchKey(8);
	newTree.insertNode(9);
	newTree.printTree();
	std::cout << std::endl;
	newTree.insertNode(2);
	// newTree.insertNode(2);
	newTree.printTree();
}