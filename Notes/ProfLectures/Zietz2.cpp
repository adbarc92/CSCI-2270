#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int addTwoNums(int oneNum, int twoNum);


int main() {
	//variables
	int anInt = 7;
	float aFloat = 7.5;
	double aDouble = 19.4548362622;
	int intArray[10];

	string socks[10];
	socks[0] = "blue";
	socks[1] = "red";

	//2D arrays
	int aTwoDeeArray[10][10];

	char myChar = 'a';

	string girlsName = "arya";

	if (girlsName == "arya") {
		cout << "a\ngirl\nis\nno\none\n";
		cout << "demoing the endl" << endl;	
	} 

	else if (girlsName == "waif") {
		cout << "SPOILER ALERT" << endl;
	}
	else {
		cout << "i don't know who you are" << endl;
	}

	for (int i=0; i<10; i++) {
		for (int j=0; j<10; j++) {
			aTwoDeeArray[i][j] = i*j;
			cout << addTwoNums(i,j) << endl;
		}
	}
	int counter = 0;
	while (counter <10) {
		cout << "counter is " << ++counter << endl;
	}




}

int addTwoNums(int oneNum, int twoNum) {
	return oneNum + twoNum;

}