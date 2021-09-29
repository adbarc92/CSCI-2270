#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <ctime>
#include <functional>
#include <queue>

#include "Entry.hpp"
#include "PQueueH.hpp"
#include "PQueueBH.hpp"
#include "PQueueLL.hpp"

using namespace std;

int read_csv(const string& filename, Entry entries[])
{
	int i		= 0;
	string line = "";
	fstream csv;

	csv.open(filename);
	if (!csv)
	{
		cout << "Error reading file: " << filename << endl;
	}

	getline(csv, line);
	while (getline(csv, line))
	{
		Entry& e = entries[i];
		string time_to_birth_str, time_treatment_str;
		stringstream ss(line);
		getline(ss, e.name, ',');
		getline(ss, time_to_birth_str, ',');
		getline(ss, time_treatment_str, ',');
		e.time_to_birth = stoi(time_to_birth_str);
		e.time_treatment = stoi(time_treatment_str);
		i++;
	}

	return i;
}

void time_code(std::function<void()> cb, int iterations)
{
	clock_t	start;
	double	duration;

	cout << "iterations: " << iterations << endl;

	start = clock();
	for (int i = 0; i < iterations; i++)
	{
		cb();
	}

	duration = (clock() - start) / (double) CLOCKS_PER_SEC;
	cout << "Duration: " << duration << "s" << endl;
	cout << "avg: " << duration / iterations << "s" << endl;
}

int main()
{
	int ntimes = 5000;
	Entry entries[880];
	int len;

	len = read_csv("patientData2270.csv", entries);

	cout << "PQueueH: " << endl;
	time_code([&]() {
		PQueueH pq;
		for (int i = 0; i < len; i++)
		{
			pq.enqueue(&entries[i]);
		}
		for (int i = 0; i < len; i++)
		{
			pq.dequeue();
		}
	}, ntimes);

	cout << "PQueueBH: " << endl;
	time_code([&]() {
		PQueueBH pq;
		for (int i = 0; i < len; i++)
		{
			pq.enqueue(&entries[i]);
		}
		for (int i = 0; i < len; i++)
		{
			pq.dequeue();
		}
	}, ntimes);

	cout << "PQueueLL: " << endl;
	time_code([&]() {
		PQueueLL pq;
		for (int i = 0; i < len; i++)
		{
			pq.enqueue(&entries[i]);
		}
		for (int i = 0; i < len; i++)
		{
			pq.dequeue();
		}
	}, ntimes);

	cout << "PQueueSTD: " << endl;
	time_code([&]() {
		priority_queue<Entry*, vector<Entry*>, CompareEntryPointers> pq;
		for (int i = 0; i < len; i++)
		{
			pq.push(&entries[i]);
		}
		for (int i = 0; i < len; i++)
		{
			pq.pop();
		}
	}, ntimes);

	return 0;
}