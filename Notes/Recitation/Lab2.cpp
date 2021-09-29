#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char* argv[]) // Int number of arguments (always at least one: a.out)
{
	std::ifstream inFile;
	std::string data;

	inFile.open(argv[1]); // Open the file
	if (inFile.is_open()) // Error check
	{
		std::cout << "Opened successfully" << std::endl;
		while (getline(inFile, data))
		{
			//Read/get every line of the file and store it
			std::cout << data << std::endl;
			//Can see the data (each line) printed

			std::stringstream ss(data);
			//Create a stringstream variable from the string data

			int elementOne;
			ss >> elementOne;
			std::cout << elementOne << std::endl;
			std::string elementTwo;
			ss >> elementTwo;
			std::cout << elementTwo << std::endl;
		}
		inFile.close();
	}
	else
		std::cout << "File unsuccessfully opened" << std::endl;
	return 0;
}

