#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <functional>
#include <queue>
#include <chrono>

#include "PQueueHelper.hpp"
#include "PQueueBH.hpp"
#include "PQueueLL.hpp"

int read_csv( const std::string& fileName, Patient patients[] )
{
	int i = 0;
	std::string line = "";
	std::fstream csv;

	csv.open( fileName );
	if ( !csv )
	{
		std::cout << "Error reading file: " << fileName << std::endl;
	}

	getline( csv, line );
	while ( getline( csv, line ) )
	{
		Patient& p = patients[ i ];
		std::string priority, treatment;
		std::stringstream ss( line );
		getline( ss, p.name, ',' );
		getline( ss, priority, ',' );
		getline( ss, treatment, ',' );
		p.priority = stoi( priority );
		p.treatment = stoi( treatment );
		i++;
	}

	return i;
}

void create_csv( std::vector< float > durationsBH, std::vector< float > durationsLL, std::vector< float > durationsSTD )
{
	std::ofstream myFile( "runtime.csv" );

	myFile << "BinaryHeap,LinkedList,PriorityQueue,\n"; // Headers

	for (int i = 0; i < 500; ++i)
	{
		myFile << std::to_string(durationsBH[ i ]) + ",";
		myFile << std::to_string(durationsLL[ i ]) + ",";
		myFile << std::to_string(durationsSTD[ i ]) + ",";
		myFile << "\n";
	}

	myFile.close();
}

Patient* makePatient( std::string name, int priority, int treatment )
{
	Patient* newPatient = new Patient;
	newPatient->name = name;
	newPatient->priority = priority;
	newPatient->treatment = treatment;

	return newPatient;
}

float timeSTD( Patient patients[] )
{
	auto startSTD = std::chrono::system_clock::now();
	
	std::priority_queue< Patient*, std::vector< Patient* >, ComparePatientPointers > pq; // Builds priority queue: data type, data structure, comparison method

	for (int i = 0; i < 880; ++i) // Enqueue - Remove hardcoding, if time allows
	{
		Patient* curPatient = makePatient( patients[ i ].name, patients[ i ].priority, patients[ i ].treatment );
		pq.push( curPatient );
	}

	for (int i = 0; i < int( pq.size() ); ++i) // Dequeue
	{
		pq.top();
		pq.pop();
	}

	auto endSTD = std::chrono::system_clock::now();
	auto timeElapsedSTD = std::chrono::duration< float >( endSTD - startSTD );

	return timeElapsedSTD.count();
}

float timeLL( Patient patients[] )
{
	auto startLL = std::chrono::system_clock::now();
	
	PQueueLL pq;
	for (int i = 0; i < 880; ++i) // Enqueue
	{
		Patient* curPatient = makePatient( patients[ i ].name, patients[ i ].priority, patients[ i ].treatment );
		pq.enqueue( curPatient );
	}

	for (int i = 0; i < 880; ++i) // Dequeue
	{
		pq.dequeue();
	}

	auto endLL = std::chrono::system_clock::now();
	
	auto timeElapsedLL = std::chrono::duration< float >( endLL - startLL );

	return timeElapsedLL.count();
}

float timeBH( Patient patients[] )
{
	auto startBH = std::chrono::system_clock::now();

	PQueueBH pq;
	
	for (int i = 0; i < 880; ++i) // Enqueue
	{
		Patient* curPatient = makePatient( patients[ i ].name, patients[ i ].priority, patients[ i ].treatment );
		pq.enqueue( curPatient ); // Could replace with &patients[ i ];
	}

	for (int i = 0; i < 880; ++i)
	{
		pq.dequeue();
	}

	auto endBH = std::chrono::system_clock::now();
	
	auto timeElapsedLL = std::chrono::duration< float >( endBH - startBH );

	return timeElapsedLL.count();
}

int main()
{
	Patient patients[ 880 ];
	std::string fileName = "patientData2270.csv";
	read_csv( fileName, patients );
	
	std::vector< float > durationsBH;
	std::vector< float > durationsLL;
	std::vector< float > durationsSTD;

	for (int i = 0; i < 500; ++i)
	{
		float duration = timeBH( patients );
		durationsBH.push_back( duration );
	}

	for (int i = 0; i < 500; ++i)
	{
		float duration = timeLL( patients );
		durationsLL.push_back( duration );
	}

	for (int i = 0; i < 500; ++i)
	{
		float duration = timeSTD( patients );
		durationsSTD.push_back( duration );
	}

	create_csv( durationsBH, durationsLL, durationsSTD );
}