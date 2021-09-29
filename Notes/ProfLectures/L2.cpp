#include <iostream>
#include <fstream> //file stream
#include <sstream> //string stream

//using namespace std;

struct Student{
	//ID, name, major
	int ID;
	std::string name;
	std::string major;
	Student(){}
	Student(int id, std::string n, std::string m){
		ID = id;
		name = n;
		major = m;
	}
};

int main(){
	std::cout<<"hello world";
	//create instance of Student called s
	Student s;
	s.ID = 5; //setting the ID property for Student s to 5
	s.name = "bob";
	s.major = "skiing";	
	Student s2(6, "jimmy","swimming");

	std::cout<<s2.ID<<" "<<s2.name<<" "<<s2.major<<std::endl;

	//arrays
	int a[10]; //array of 10 integers called a
	for(int i = 0; i < 10; i++){
		a[i] = i; //initialize a[i] to i
		std::cout<<a[i]<<std::endl;
	}
	int b[10];
	//b = a; //this does not copy a into b
	std::cout<<"a="<<a<<std::endl; //prints address of a
	//array of Students
	//this will be populated with file data
	Student allStudents[10];
	//streams
	std::ifstream myfile("students.txt");
	if(myfile.is_open()){
		//read the file
		std::string line;
		int counter = 0;
		while(getline(myfile, line)){
			std::cout<<line<<std::endl;
			//string stream - include sstream
			std::stringstream ss;
			//write line string into string stream
			ss<<line;
			std::string item;
			
			getline(ss, item, ',');
			allStudents[counter].ID = stoi(item);
			//how do I read name?
			getline(ss, item, ',');
			allStudents[counter].name = item;

			getline(ss, item);
			allStudents[counter].major = item;

			counter++;

		}

	}else{
		std::cout<<"error"<<std::endl;
	}
	//verify contents of allStudents array
	for(int i = 0; i < 10; i++){
		std::cout<<allStudents[i].ID<<" "<<allStudents[i].name<<" "<<allStudents[i].major<<std::endl;
	}
}