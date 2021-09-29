#include <iostream>

//command line args are arguments to the main function
//which runs when the program runs
//argc is number of arguments
//*argv is an array of pointers to the arguments
int main(int argc, char *argv[]){
	std::cout<<"hello world"<<std::endl;

	std::cout<<argc<<std::endl;
	//argv[0] is name of program running
	std::cout<<argv[0]<<std::endl;

	//std::cout<<argv[1]<<std::endl;

	//loop through arguments
	//don't have to know how many arguments because that is set with argc

	for(int i = 0; i < argc; i++){
		std::cout<<argv<<std::endl;
	}


}