#include <iostream>

struct node{
	int key;
	node *next;
	node(int k, node *n){
		key = k;
		next = n;
	}
};
int main(){

	node *x = new node(5, NULL);
	std::cout<<x->key<<std::endl; //(*x).key
	std::cout<<(*x).key<<std::endl; //(*x).key

	node *x2 = new node(6, NULL);
	x->next = x2;
	std::cout<<x2<<std::endl;
	std::cout<<x->next<<std::endl;

	x2->key = 10;
	std::cout<<x->next->key<<std::endl;

	int *p = new int[5];
	std::cout<<p<<std::endl;
	p++;
	std::cout<<p<<std::endl;

	//delete[] p;
	int *p2 = new int;
	p2++;
	delete p2;
	
}