#include <iostream>
#include <string>

struct NodeRBT
{
	int key;
	std::string color;
	NodeRBT* leftChild;
	NodeRBT* rightChild;
	NodeRBT* parent;
	
	NodeRBT( int value )
	{
		key = value;
		color = "black";
		leftChild = nullptr;
		rightChild = nullptr;
		parent = nullptr;
	}

};

class RedBlackTree
{
	public:
		RedBlackTree();
		~RedBlackTree();
		void insertNode( int value );
		NodeRBT* search( int value );
		void deleteTree( NodeRBT* node );
		void visualizeTree();

		void leftRotate( int value );
		void rightRotate( int value );

	protected:

	private:
		NodeRBT* root;

		void insertRB( int value );
		NodeRBT* searchRB( int value );
		void balanceRB( NodeRBT* node );
		void printAll( NodeRBT* node );
		void visualizeTree( NodeRBT* node, int indent);

		NodeRBT* findMinimum( NodeRBT* node );

};