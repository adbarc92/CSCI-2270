#pragma once // Header Guard: makes end result of compilation faster, does not prevent any errors
#include <string>

struct Patient
{
	std::string name;
	int priority;
	int treatment;
};

inline bool shouldComeBefore(const Patient* a, const Patient* b) // Returns true if a should come before b
{
	if (a->priority < b->priority)
	{
		return true;
	}
	else if (b->priority < a-> priority)
	{
		return false;
	}
	else
	{
		if (a->treatment < b->treatment)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

struct ComparePatientPointers
{
	bool operator()( const Patient* p1, const Patient* p2 )
	{
		return !shouldComeBefore(p1, p2);
	}
};

