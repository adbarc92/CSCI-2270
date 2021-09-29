#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct student {
	int studentID = -1;
	string studentName = "n/a";
	string studentMajor = "n/a";
};


int main() {
	//make array of students
	student studentArray[10];
	int numStudents = 0;
	//file i/o
	ifstream inFile;

	string myTextFile = "students.txt";
	//open file
	inFile.open(myTextFile);
	if (inFile.fail()) {
		cout << "problem opening file" << endl;
	}
	else {
		//process data
		cout << "file opened properly" << endl;
		//read through each line
		string currentLine;
		while(getline(inFile,currentLine)) {
			cout << "i just read: " << currentLine << endl;
		}
		//start over
		inFile.clear();
		inFile.seekg(0,ios::beg);

		while(getline(inFile,currentLine)) {
			//set up string stream
			stringstream curStrStream(currentLine);
			string curID, curSName, curSMaj = "";
			getline(curStrStream,curID,',');
			getline(curStrStream,curSName,',');
			getline(curStrStream,curSMaj,',');
			cout << "id: " << curID << endl;
			cout << "name: " << curSName << endl;
			cout << "major: " << curSMaj << endl;
			studentArray[numStudents].studentID = stoi(curID);
			studentArray[numStudents].studentName = curSName;
			studentArray[numStudents].studentMajor = curSMaj;
			numStudents++;
		}
	}
	inFile.close();

	//let's try writing to a file
	ofstream outFile;
	outFile.open("studentinfo.txt");

	//iterate through the data we just stored
	for (int i=0; i<numStudents; i++) {
		outFile << studentArray[i].studentID << "\t" << studentArray[i].studentName << "\t" << studentArray[i].studentMajor << "\n";
	}
	outFile.close();

}