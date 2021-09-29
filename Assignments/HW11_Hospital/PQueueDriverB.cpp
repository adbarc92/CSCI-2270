#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <ctime>
#include <functional>
#include <queue>

#include "PQueueHelper.hpp"
#include "PQueueH.hpp"
#include "PQueueBH.hpp"
#include "PQueueLL.hpp"

int read_csv(const std::string& filename, Patient patients[])
{
	int i = 0;
	std::string line = "";
	std::fstream csv;

	csv.open(filename);
	if (!csv)
	{
		std::cout << "Error reading file: " << filename << std::endl;
	}

	getline(csv, line);
	while (getline(csv, line))
	{
		Patient& p = patients[i];
		std::string time_to_birth_str, time_treatment_str;
		std::stringstream ss(line);
		getline(ss, p.name, ',');
		getline(ss, time_to_birth_str, ',');
		getline(ss, time_treatment_str, ',');
		p.priority = stoi(time_to_birth_str);
		p.treatment = stoi(time_treatment_str);
		i++;
	}

	return i;
}

void time_code(std::function<void()> cb, int iterations)
{
	clock_t	start;
	double	duration;

	std::cout << "iterations: " << iterations << std::endl;

	start = clock();
	for (int i = 0; i < iterations; i++)
	{
		cb();
	}

	duration = (clock() - start) / (double) CLOCKS_PER_SEC;
	std::cout << "Duration: " << duration << "s" << std::endl;
	std::cout << "avg: " << duration / iterations << "s" << std::endl;
}

int main()
{
	int ntimes = 5000;
	Patient patients[880];
	int len;

	len = read_csv("patientData2270.csv", patients);

	std::cout << "PQueueBH: " << std::endl;
	time_code([&]() {
		PQueueBH pq;
		for (int i = 0; i < len; i++)
		{
			pq.enqueue(&patients[i]);
		}
		for (int i = 0; i < len; i++)
		{
			pq.dequeue();
		}
	}, ntimes);

	std::cout << "PQueueLL: " << std::endl;
	time_code([&]() {
		PQueueLL pq;
		for (int i = 0; i < len; i++)
		{
			pq.enqueue(&patients[i]);
		}
		for (int i = 0; i < len; i++)
		{
			pq.dequeue();
		}
	}, ntimes);

	std::cout << "PQueueSTD: " << std::endl;
	time_code([&]() {
		std::priority_queue<Patient*, std::vector<Patient*>, ComparePatientPointers> pq;
		for (int i = 0; i < len; i++)
		{
			pq.push(&patients[i]);
		}
		for (int i = 0; i < len; i++)
		{
			pq.pop();
		}
	}, ntimes);

	return 0;
}