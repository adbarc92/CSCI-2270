#include <iostream>

const int MAX_SIZE = 10;

class arrayStack
{
public:
	arrayStack();
	~arrayStack();
	bool isEmpty();
	bool isFull();
	bool push(std::string);
	std::string pop();
	std::string peek();
private:
	std::string stackOfstrings[MAX_SIZE];
	int top;
};

arrayStack::arrayStack(){};

arrayStack::~arrayStack(){};

bool arrayStack::isEmpty()
{
	if (top == 0)
	{
		return true;
	}
	else
		return false;
}

bool arrayStack::isFull()
{
	if (top == MAX_SIZE)
	{
		return true;
	}
	else
		return false;
}

bool arrayStack::push(std::string a)
{
	if (top < MAX_SIZE-1)
	{
		stackOfstrings[top] = a;
		top++;
		return true;
	}
	else
		return false;
}

std::string arrayStack::pop()
{
	if ( !isEmpty() )
	{
		top--;
		return stackOfstrings[top];
	}
	else
	{
		std::cout << "Stack is empty" << std::endl;
		return "";
	}

}

std::string arrayStack::peek()
{
	if ( ! isEmpty() )
	{
		return stackOfstrings[top-1];
	}
	else
		std::cout << "Stack is empty" << std::endl;
	return "";
}

int main()
{
	
}