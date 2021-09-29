#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

struct Patient
{
	std::string name;
	int priority;
	int treatment;
};

void read_csv1( std::string fileName, Patient patients[] )
{
	std::string curLine;
	std::stringstream ss;
	std::ifstream file( fileName );

	if ( !file )
	{
		std::cout << "Cannot read file: " << fileName << std::endl;
		return;
	}

	std::getline( file, curLine );
	// std::cout << curLine << std::endl;
	int i = 0;

	while( std::getline( file, curLine ) )
	{
		ss.clear();
		ss.str( curLine );
		std::string name, priority, treatment;

		std::getline( ss, name, ',' );
		std::getline( ss, priority, ',' );
		std::getline( ss, treatment, ',' );

		patients[ i ].name = name;
		patients[ i ].priority = stoi(priority);
		patients[ i ].treatment = stoi(treatment);

		i++;
	}
}

int read_csv2( const std::string& fileName, Patient patients[] )
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

int sreesha_read_csv( int argc, char* argv[] )
{

	// Creating the output file.

	std::ofstream myfile;
	myfile.open ("EmployeeData.csv");

	// Creating array that has Employee names
	
	myfile << "Employee Name,EmployeeSalary2018, EmployeeSalary2019, EmployeeSalary2020,\n";
	const int size = 10;
	std::string name[size] = {"Alex","Kelly","Bruce","Jane","Kenny","Roger","Katie","Molly","Shane","Rocky"};

	for (int i = 0; i < size; i++)
	{
		// Assigning Salaries for 2018, 2019 and 2020
		// Salary is assigned randomly as a number between 75000 and 100000

		double rnd = 75000 + ( std::rand() % ( 100000 - 75000 + 1 ) );
		double rnd2 = 75000 + ( std::rand() % ( 100000 - 75000 + 1 ) );
		double rnd3 = 75000 + ( std::rand() % ( 100000 - 75000 + 1 ) );

		// Writing to the csv file

		myfile << name[i]+",";
		myfile << std::to_string(rnd)+",";
		myfile << std::to_string(rnd2)+",";
		myfile << std::to_string(rnd3)+",";
		myfile << "\n";
	}

	// CLosing the CSV File
	
	myfile.close();
	return 0;
}