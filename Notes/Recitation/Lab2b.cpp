#include <iostream>
#include <fstream>
#include <sstream>

struct CarData
{
	std::string make;
	std::string model;
	std::string year;
};

int main ()
{
	std::ifstream inFile;
	std::string currentLine;

	int numCars = 0;

	CarData carArray[10];
	inFile.open("carfile.txt");
	if (inFile.is_open())
	{
		std::cout << "Opened Successfully" << std::endl;
		while (getline(inFile,currentLine))
		{
			std::stringstream curCar(currentLine); // Confusing
			std::string curMake, curModel, curYear = "";
			getline(curCar,curMake, ' ');
			getline(curCar,curModel, ' ');
			getline(curCar,curYear, ' ');

			carArray[numCars].make = curMake;
			carArray[numCars].model = curModel;
			carArray[numCars].year = curYear;
			numCars++;
		}
		inFile.close();
		std::ofstream outFile;
		outFile.open("outfile.txt");
		for (int i = 0; i < numCars; ++i)
		{
			outFile << carArray[i].make << "\t" << carArray[i].model << "\t" << carArray[i].year << "\t" << std::endl;
		}
	}
	
}

// for (int i = 0; i < 10; i++)
// 	{
// 		std::cout << " make: " << carArray[i].make << " model: " << carArray[i].model << " year:" << carArray[i].year << std::endl;
// 	}