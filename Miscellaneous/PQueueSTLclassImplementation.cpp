#include <iostream>
#include <queue>

struct Patient
{
	std::string name;
	int priority;
	Patient( std::string pName="", int pri=0)
	{
		name = pName;
		priority = pri;
	}
};

struct compare
{
	bool operator() (const Patient &a, const Patient &b )
	{
		return a.priority < b.priority;
	}
};

int main()
{
	std::priority_queue<int> pqInts;
	pqInts.push(4);
	pqInts.push(14);
	pqInts.push(34);
	pqInts.push(0);
	pqInts.push(2);

	while ( !pqInts.empty() )
	{
		std::cout << pqInts.top() << std::endl;
		pqInts.pop();
	}

	std::priority_queue< std::string > pqStrings;
	pqStrings.push("coffee");
	pqStrings.push("tea");
	pqStrings.push("water");
	while ( !pqStrings.empty() )
	{
		std::cout << pqStrings.top() << std::endl;
		pqStrings.pop();
	}

	std::priority_queue< Patient, std::vector<Patient>, compare > pq; // First: type of thing, Second: container for storage, Third:
	
	Patient p1( "quaid", 50 );
	Patient p2( "dutch", 30 );
	Patient p3( "richard", 120 );
	Patient p4( "kimble", 75 );
	Patient p5( "t800", 15 );
	Patient p6( "conan", 55 );

	pq.push(p1);
	pq.push(p2);
	pq.push(p3);
	pq.push(p4);
	pq.push(p5);
	pq.push(p6);

	while ( !pq.empty() )
	{
		std::cout << "Patient: " << pq.top().name << std::endl;

	}
}