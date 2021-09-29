#include <iostream>
#include <fstream>	//reading from and writing to file
#include <string>
#include <sstream>

using namespace std;

struct student {
	int studentID = -1;
	string studentName="n/a";
	string studentMajor="n/a";
};


int main(int argc, char* argv[]) {

	//we are expecting four things on the command line
	if (argc < 4) {
		cout << "not enough parameters for this program" << endl;


	}
	else {
		//check the parameters
		for (int i=0; i<argc; i++) {
			cout << "parameters " << i << ": " << argv[i] << endl;
		}

		//the first parameter is the name of the executable
		//second parameter is the number of lines in the file that you'll read
		//third parameter is the input file
		//fourth parameter is the output file

		//file i/o
		ifstream inFile;
		//array of student structs
		//student studentArray[argv[1]];	//why doesn't that work?  must convert argv[1]
		student studentArray[atoi(argv[1])];
		int numStudents = 0;

		//open a file
		inFile.open(argv[2]);
		//check if it opened
		if (inFile.fail()) {
			cout << "problem opening file" << endl;
		}
		else {
			cout << "file opened successfully" << endl;
			//read through the file
			string currentLine;
			//get each line
			while(getline(inFile,currentLine)) {
				//cout << "i just read this line:" << currentLine << endl;
			}
			//start over using seek
			inFile.clear();
			inFile.seekg(0,ios::beg);
			//now get each line
			while(getline(inFile,currentLine)) {
				//get each thing
				//set up a stringstream
				stringstream curStrStream(currentLine);
				string curSID,curSName,curSMaj = "";
				getline(curStrStream,curSID,',');
				getline(curStrStream,curSName,',');
				getline(curStrStream,curSMaj,',');

				//double-check that what you got is what you expect
				cout << "id: " << curSID;
				cout << " name: " << curSName;
				cout << " major: " << curSMaj << endl;

				//assign variables to the "next" item in the array
				//cast SID as an int when storing it in the struct
				studentArray[numStudents].studentID = stoi(curSID);
				studentArray[numStudents].studentName = curSName;
				studentArray[numStudents].studentMajor = curSMaj;
				numStudents++;
			}
		}
		inFile.close();

		//let's try writing to a file
		ofstream outFile;
		outFile.open(argv[3]);	//this wipes anything already in the file

		//iterate through the data we just stored and write it to the output file
		//write items spaced by tabs
		//technically you can use stoi(argv[1]) instead of numStudents in the for loop
		for (int i=0;i<numStudents;i++) {
			outFile << studentArray[i].studentID << "\t" << studentArray[i].studentName << "\t" << studentArray[i].studentMajor << "\n";
		}
		outFile.close();
	}
}

