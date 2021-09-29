#include "PQueueH.hpp"

#include <stdexcept>
#include <iostream>

using namespace std;

PQueueH::PQueueH()
{
	size = 0;
	list = nullptr;
}
PQueueH::~PQueueH()
{
	delete [] list;
}

void PQueueH::enqueue(Entry* e)
{
	size++;
	Entry** new_list = new Entry*[size];

	bool inserted = false;
	for (int i = 0; i < size; i++)
	{
		if (inserted)
		{
			new_list[i] = list[i - 1];
		}
		else if (i < size - 1)
		{
			if (should_come_before(list[i], e))
			{
				new_list[i] = list[i];
			}
			else
			{
				new_list[i] = e;
				inserted = true;
			}
		}
		else
		{
			new_list[i] = e;
		}
	}

	if (list != nullptr)
	{
		delete [] list;
	}

	list = new_list;
}

Entry* PQueueH::dequeue()
{
	size--;
	if (size < 0)
	{
		throw std::runtime_error("cannot dequeue an empty list");
	}

	Entry* ret = list[0];

	if (size == 0)
	{
		delete [] list;
		list = nullptr;
		return ret;
	}

	Entry** new_list = new Entry*[size];
	memcpy(new_list, list, size * sizeof(Entry*));

	delete [] list;
	list = new_list;
	return ret;
}