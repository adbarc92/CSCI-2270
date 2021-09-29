#include <iostream>
using namespace std;

struct Node {
	int id = -1;
	Node* left = nullptr;
	Node* right = nullptr;
	Node* parent = nullptr;
};

class BST {
	private:
		Node* root = nullptr;
		Node* createNode(int,Node*,Node*,Node*);
		int getSize(Node*);
		bool addNodeRPriv(Node*,int);
		Node *search(Node*,int);
		/*new code for lecture 18*/
		bool deleteNode(Node*,int);
		int getMinInSubtree(Node*);	//where Node* is the root of the subtree where we're looking
		int getMaxInSubtree(Node*);
		/*new code for lecture 19*/
		void printNodesInOrder(Node*);	//where Node* is where you start from
		void printNodesPreOrder(Node*);
		void printNodesPostOrder(Node*);
	public:
		BST();
		~BST();
		bool addNode(int);
		bool addNodeR(int);
		
		bool findSmallestNode(int&);
		bool findLargestNode(int&);
		int getSizeOfTree();
		/*new in 18*/
		bool deleteItem(int);
		/*new in 19*/
		void printTree(string);
};

BST::BST() {

}

BST::~BST() {

}

Node* BST::createNode(int itemToAdd, Node* parentNode, Node* leftChild, Node* rightChild) {
	Node* newNode = new Node;
	newNode->id = itemToAdd;
	newNode->parent = parentNode;
	newNode->left = leftChild;
	newNode->right = rightChild;

	return newNode;
}

bool BST::findLargestNode(int& itemToFind) {
	if (root != nullptr) {
		Node* tmpNode = root;
		while (tmpNode->right != nullptr) {
			tmpNode = tmpNode->right;
		}
		itemToFind = tmpNode->id;
		return true;
	}
	else {
		return false;
	}
}


int BST::getSizeOfTree() {
	return getSize(root);
}

int BST::getSize(Node* startNode) {
	int size=0;
	if (startNode != nullptr) {
		size++;
		size+=getSize(startNode->left);
		size+=getSize(startNode->right); 
	}
	return size;
}

bool BST::addNode(int itemToAdd) {
	//start at root
	Node* tmpNode = root;
	Node* curParent = nullptr;

	while (tmpNode != nullptr) {
		curParent = tmpNode;
		if (itemToAdd == tmpNode->id) {
			cout << "item already in tree" << endl;
			return false;
		}
		else {
			if (itemToAdd < tmpNode->id) {
				tmpNode = tmpNode->left;
			}
			else {
				tmpNode = tmpNode->right;
			}
		}
	}
	if (curParent == nullptr) {
		root = createNode(itemToAdd,nullptr,nullptr,nullptr);
		cout << "item " << itemToAdd << " added as root" << endl;
	}
	else if (itemToAdd < curParent->id) {
		curParent->left = createNode(itemToAdd,curParent,nullptr,nullptr);
		cout << "item " << itemToAdd << " added to left of " << curParent->id << endl;
	}
	else {
		curParent->right = createNode(itemToAdd,curParent,nullptr,nullptr);
		cout << "item " << itemToAdd << " added to right of " << curParent->id << endl;
	}
	return true;
}

bool BST::addNodeR(int itemToAdd) {
	if (root == nullptr) {
		Node * newNode = createNode(itemToAdd,nullptr,nullptr,nullptr);
		root = newNode;
		cout << "item " << itemToAdd << " added as root" << endl;
		return true;
	}
	else {
		return addNodeRPriv(root,itemToAdd);
	}
}

bool BST::addNodeRPriv(Node* curNode, int itemToAdd) {
	if (itemToAdd < curNode->id) {
		if (curNode->left != nullptr) {
			return addNodeRPriv(curNode->left, itemToAdd);
		}
		else {
			curNode->left = createNode(itemToAdd,curNode,nullptr,nullptr);
			cout << "item " << itemToAdd << " added to left of "<< curNode->id << endl;
			return true;
		}
	}
	else if (itemToAdd > curNode->id) {
		if (curNode->right != nullptr) {
			return addNodeRPriv(curNode->right, itemToAdd);
		}
		else {
			curNode->right = createNode(itemToAdd,curNode,nullptr,nullptr);
			cout << "item " << itemToAdd << " added to right of "<< curNode->id << endl;
			return true;
		}
	}
	else {
		cout << "item " << itemToAdd << " already in tree" << endl;
		return false;
	}
}

Node* BST::search(Node* startNode, int itemToFind) {
	if (startNode != nullptr) {
		if (itemToFind < startNode->id && startNode->left != nullptr) {
			return search(startNode->left, itemToFind);
		}
		else if (itemToFind > startNode->id && startNode->right != nullptr) {
			return search(startNode->right, itemToFind);
		}
		else if (itemToFind == startNode->id) {
			return startNode;
		}
		else {
			//item not in tree
			return nullptr;
		}
	}
	else {
		return nullptr;
	}
}

int BST::getMinInSubtree(Node* startNode) {
	if (startNode != nullptr) {
		while (startNode->left != nullptr) {
			startNode = startNode->left;
		}
		return startNode->id;
	}
	else {
		return -99999999;
	}
}

int BST::getMaxInSubtree(Node* startNode) {
	if (startNode != nullptr) {
		while (startNode->right != nullptr) {
			startNode = startNode->right;
		}
		return startNode->id;
	}
	else {
		return -99999999;
	}
}

bool BST::deleteNode(Node* startNode, int itemToFind) {
	Node* target = search(startNode, itemToFind);
	if (target != nullptr) {
		//first, check right
		if (target->right != nullptr) {
			int minRight = getMinInSubtree(target->right);
			Node* minRightNode = search(target->right, minRight);
			cout << "min right node: " << minRightNode->id << endl;
			if (minRightNode->right != nullptr) {
				//minRight node has a child. it can't have a left child, though, because otherwise it wouldn't be the minimum in the right subtree
				minRightNode->right->parent = minRightNode->parent;
				minRightNode->parent->left = minRightNode->right;
			}
			else {
				//no child nodes
				minRightNode->parent->right = nullptr;
			}
			delete minRightNode;//not actually deleting the thing that we're "deleting"
			target->id = minRight;
			return true;
		}
		else if (target->right != nullptr) {
			//run getMax on left

			return true;
		}
		else {
			//target has no childen, delete is easy peezy

			return true;
		}

	}
	else {
		//target not found
		return false;
	}
}

bool BST::deleteItem(int itemToFind) {
	//write a wrapper to see if the item is in the root and there's nothing else?
	return deleteNode(root, itemToFind);
}


void BST::printTree(string printOption) {
	if (printOption == "InOrder") {
		printNodesInOrder(root);
	}
	else if (printOption == "PreOrder") {
		//for you to finish
	}
	//for you to finish
}

void BST::printNodesInOrder(Node* startNode) {
	//print left, node, then right
	if (startNode != nullptr) {
		if (startNode->left != nullptr) {
			printNodesInOrder(startNode->left);
		}
		cout << startNode->id << endl;
		if (startNode->right != nullptr) {
			printNodesInOrder(startNode->right);
		}
	}
}





int main() {
	BST niceTree;
	/*non-recursive add*/
/*
	niceTree.addNode(17);
	niceTree.addNode(42);
	niceTree.addNode(12);
	niceTree.addNode(18);
	niceTree.addNode(18);
*/
	/*recursive add*/
	niceTree.addNodeR(17);
	niceTree.addNodeR(42);
	niceTree.deleteItem(17);
	niceTree.addNodeR(12);
	niceTree.addNodeR(11);
	niceTree.addNodeR(18);

	niceTree.printTree("InOrder");


	return 0;
}













