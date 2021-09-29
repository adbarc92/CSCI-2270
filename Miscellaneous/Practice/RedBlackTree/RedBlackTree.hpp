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
		void insertNode2( int value );
		NodeRBT* search( int value );
		void deleteTree();
		void visualizeTree();

	protected:

	private:
		NodeRBT* root;
		void leftRotate( NodeRBT* node );
		void rightRotate( NodeRBT* node );
		void insertRB( int value );
		void balanceRB( NodeRBT* node );
		void printAll( NodeRBT* node );
		void visualizeTree( NodeRBT* node, int indent);

		NodeRBT* findMinimum( NodeRBT* node );

};