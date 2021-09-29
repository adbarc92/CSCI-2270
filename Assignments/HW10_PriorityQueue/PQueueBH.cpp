#include  "PQueueBH.hpp"

#include <stdexcept>
#include <iostream>

using namespace std;

PQueueBH::PQueueBH()
{
	size = 0;
	heap = nullptr;
}

PQueueBH::~PQueueBH()
{
	delete [] heap;
}

void PQueueBH::enqueue(Entry* e)
{
	size++;
	Entry** new_heap = new Entry*[size];
	memcpy(new_heap, heap, (size - 1) * sizeof(Entry*));

	int i = size - 1;
	int parent_i = getParentIndex(i);
	new_heap[i] = e;

	while (should_come_before(e, new_heap[parent_i]) && i > 0)
	{
		Entry* tmp = new_heap[i];
		new_heap[i] = new_heap[parent_i];
		new_heap[parent_i] = tmp;
		i = parent_i;
		parent_i = getParentIndex(i);
	}

	if (heap != nullptr)
	{
		delete [] heap;
	}
	heap = new_heap;
}

Entry* PQueueBH::dequeue()
{
	if (size <= 0)
	{
		throw std::runtime_error("cannot dequeue an empty list");
	}

	Entry* ret = heap[0];
	heap[0] = heap[size - 1];
	size--;

	if (size == 0)
	{
		delete [] heap;
		heap = nullptr;
		return ret;
	}

	Entry** new_heap = new Entry*[size];
	memcpy(new_heap, heap, size * sizeof(Entry*));
	delete [] heap;
	heap = new_heap;
	rebuildHeap(0);

	return ret;
}

void PQueueBH::rebuildHeap(int i)
{
	int left_i = getLeftIndex(i);
	int right_i = getRightIndex(i);
	int smallest_i = i;
	if (left_i < size && should_come_before(heap[left_i], heap[i]))
	{
		smallest_i = left_i;
	}
	if (right_i < size && should_come_before(heap[right_i], heap[smallest_i]))
	{
		smallest_i = right_i;
	}
	if (smallest_i != i)
	{
		Entry* tmp = heap[i];
		heap[i] = heap[smallest_i];
		heap[smallest_i] = tmp;
		rebuildHeap(smallest_i);
	}
}

int PQueueBH::getParentIndex(int i)
{
	return (i - 1) / 2;
}
int PQueueBH::getLeftIndex(int i)
{
	return (2 * i + 1);
}
int PQueueBH::getRightIndex(int i)
{
	return (2 * i + 2);
}
