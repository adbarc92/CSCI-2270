#include <iostream>
#include "Lab5doublyLL.cpp"

int main()
{
	doublyLL* linkedList = new doublyLL(1);
	int count = 0;

	for (int i = 0; i < 5; ++i)
	{
		linkedList->insertNodeAtEnd(i+0);
		linkedList->insertNodeAtEnd(i+1);
		linkedList->insertNodeAtEnd(i+2);
		linkedList->insertNodeAtEnd(i+3);
		count = count + 4;
	}
	linkedList->deleteNode(4);
	linkedList->print_list();
	std::cout << "Count: " << count << std::endl;
}