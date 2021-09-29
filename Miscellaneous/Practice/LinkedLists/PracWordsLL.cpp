#include <iostream>
#include <string>
#include "LinkedList.h"
#define Text "the sentence is important for some completely unknown reason"

int countWords(std::string str)
{
	short count = 1;
	for (int i = 0; i < (str.length()); ++i)
	{
		if (str[i] == ' ')
		{
			count = count + 1;
		}
	}
	return count;
}

void loadWords(std::string str)
{
	LinkedList* ll = new LinkedList();
	int length = str.length();
	std::string payload = "";
	for (int i = 0; i < length; ++i)
	{
		if (str[i] == ' ')
		{
			ll->add(payload);
			payload.clear();
		}
		else 
		{
			payload += str[i];
		}
	}
}

int main()
{
	LinkedList* ll;

	std::string arr[15];
	std::string str = Text;
	int count = countWords(str);
	loadWords(arr,str);
	for (int i = 0; i < count; ++i)
	{
		std::cout << arr[i] << std::endl;
	}
	return 0;
}