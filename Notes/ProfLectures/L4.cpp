#include <iostream>

void passByValue(int a){
	a++;
}
void passByPointer(int *ptr){
	std::cout<<"address stored in ptr:"<<ptr<<std::endl;
	*ptr = *ptr + 1;
	(*ptr)++;
}
int main(){
	
	int a = 5; //regular variable
	std::cout<<&a<<std::endl;

	//pointer and address it points to have to be same type
	int *b = &a; //b is a pointer. It stores the address of a
	//* has two meanings
	//use it to declare pointer
	//use it to dereference the pointer
	//dereference - go to address stored in pointer and get the value at that address

	std::cout<<&b<<", "<<b<<", "<<*b<<std::endl;

	a = 10;
	//what is value of *b? It has changed to 10
	std::cout<<&b<<", "<<b<<", "<<*b<<std::endl;

	int c = 20;
	b = &c; //change the address stored in b to address of c
	std::cout<<*b<<std::endl; //prints 20

	int arrayA[5];
	std::cout<<arrayA<<std::endl; //name of array gives us address of first element in array

	//functions
	passByValue(a);
	std::cout<<a<<std::endl; //prints a 10, a unchanged
	std::cout<<"address stored in b:"<<b<<std::endl;
	passByPointer(b); //updates the value at the address stored in b
	std::cout<<*b<<std::endl;

	



}