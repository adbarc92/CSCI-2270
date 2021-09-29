void testLL( Patient patients[] ) // Test first 20
{
	PQueueLL pq;
	for (int i = 0; i < 880; ++i) // Enqueue
	{
		Patient* curPatient;
		curPatient->name = patients[ i ].name;
		curPatient->priority = patients[ i ].priority;
		curPatient->treatment = patients[ i ].treatment;
		pq.enqueue( curPatient );
	}

	for (int i = 0; i < 20; ++i) // Dequeue
	{
		Patient* P = pq.dequeue();
		std::cout << "Name: " << P->name << " " << P->priority << " " << P->treatment << std::endl;
	}
}

void testSTD( Patient patients[] ) // Test first 20
{
	std::priority_queue< Patient*, std::vector< Patient* >, ComparePatientPointers > pq;
	
	for (int i = 0; i < 20; ++i)
	{
		pq.push( &patients[ i ]);
	}

	for (int i = 0; i < 20; ++i)
	{
		Patient* P = pq.top();
		pq.pop();
		std::cout << "Name: " << P->name << " " << P->priority << " " << P->treatment << std::endl;
	}
}