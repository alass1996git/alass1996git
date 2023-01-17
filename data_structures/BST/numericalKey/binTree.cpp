#include "binTree.h"

// constructor for the binary tree.
// initializes the root to be a null pointer
binTree::binTree(){
	root = NULL;
}
// destructor for the binary tree
binTree::~binTree(){
	destruct(root);
}
int binTree::emptyCheck(){
	if (root){
		return 1;
	}
	std::cout << "bst is empty" << std::endl;
	return 0;
}
// destruct - helper function to propagate through binTree 
// to clean destruct the tree. 
void binTree::destruct(bstNode *curr){
	if(curr){
		// destruct the left branch of the tree and right branch of the
		// tree before deleteing this node.
		if(curr->left){
			destruct(curr->left);
		}	
		if(curr->right){
			destruct(curr->right);
		}
		delete curr;
	}
}
void binTree::propagate(bstNode *input, bstNode *curr){
	// key is less than root's data: propagate left 
	if (input->data.key < (curr->data).key) {
		if (!curr->left){
			// add left if no left node.
			curr->left = input;
		}
		else{
			propagate(input, curr->left);
		}
	}
	// key is greater than root's data: propagate right
	else if (input->data.key > (curr->data).key) {
		// add right if no right node.
		if (!curr->right){
			curr->right = input;
		}
		else{
			propagate(input, curr->right);
		}
	}
	// keys cannot be equal. Print error and quit
	else{
		std::cout << "key already exists: " << (input->data).key << std::endl;
		exit(-1);
	}
}

// overloaded function so user doesn't need to input root
void binTree::printKeys(){
	if(!emptyCheck()){return;}
	printKeys(root);
	std::cout << std::endl;
}
// prints the keys in order
void binTree::printKeys(bstNode *curr){
	// propagate left if possible
	if(curr->left){
		printKeys(curr->left);
	}	
	// at this point, everything less than the current node has been printed.
	// print current value.
	std::cout << curr->data.key << ',';
	// recursively print values greater than the current node's value
	if(curr->right){
		printKeys(curr->right);
	}
}
void binTree::addNode(bstData inputData){
	// initialize new node given the data on hand.
	bstNode *newNode = new bstNode;
	newNode->data = inputData;
	newNode->left = NULL;
	newNode->right = NULL;
	// if no root, set the new node as the root.
	if(!root){
		root = newNode;
	}
	else{
		propagate(newNode, root);
	}
}
// overloaded function for searching. Avoids having to add root to the call
bstData binTree::search(keyType val){
	bstNode *result;
	if(!emptyCheck()){
		std::cout << "FATAL: retrieving data from an uninitialized list." << std::endl;
		exit(1);
	}
	result = search(val, root);
	return result->data;
}
bstNode *binTree::search(keyType val, bstNode *curr){
	if (!curr){
		std::cout << "FATAL: error in bst::search() - " << val << " not found" << std::endl;
		exit(1);
	}
	if (curr->data.key == val){
		return curr;
	}
	else if(curr->data.key > val){
		return search(val, curr->left);
	}	
	else{
		return search(val, curr->right);
	}
}
void binTree::deleteKey(keyType val){
	if(!emptyCheck()){
		std::cout << "FATAL: deleting data from an uninitialized list." << std::endl;
		exit(1);
	}
	deleteKey(val, root);
}
bstNode *binTree::deleteKey(keyType val, bstNode *curr){
	if(!curr){
		std::cout << "FATAL: key marked for deletion not found" << std::endl;
		exit(1);
	}
	if(val < curr->data.key){
		curr->left = deleteKey(val, curr->left);
	}
	else if(val > curr->data.key){
		curr->right = deleteKey(val, curr->right);
	}
	else{
		std::cout << "found node for deletion" << std::endl;
		if (curr->left && curr->right){
			bstNode *parent = curr;
			bstNode *successor = curr->right;
			while (successor->left){
				parent = successor;
				successor = successor->left;
			}
			curr->data = successor->data;
			parent->right = successor->right;
			delete successor;
		}
		else if (curr->left){
			std::cout << "condition" << std::endl;
			curr->data = curr->left->data;
			bstNode *tempLeft = curr->left->left;
			bstNode *tempRight = curr->left->right;
			delete curr->left;
			curr->left = tempLeft;
			curr->right = tempRight;
		}
		else if (curr->right){
			std::cout << "condition" << std::endl;
			curr->data = curr->right->data;
			bstNode *tempLeft = curr->right->left;
			bstNode *tempRight = curr->right->right;
			delete curr->right;
			curr->left = tempLeft;
			curr->right = tempRight;
		}
		else{
			delete curr;
			return NULL;
		}
	}
	return curr;
}

void addTo(binTree *bt, keyType val){
	bstData btData;
	btData.key = val;
	bt->addNode(btData);
}

int main(){
	binTree *bt;
	bt = new binTree;

	addTo(bt, 00.0);
	addTo(bt, 40.0);
	addTo(bt, 20.0);
	addTo(bt, 10.0);
	addTo(bt, 50.0);
	addTo(bt, 60.0);
	addTo(bt, 43.0);
	addTo(bt, 47.0);
	addTo(bt, 42.3);
	addTo(bt, 24.0);
	addTo(bt, 11.0);
	addTo(bt, 55.0);
	addTo(bt, 63.0);
	addTo(bt, -10.0);
	addTo(bt, -5.0);

	bt->printKeys();
	bt->deleteKey(-5.0);
	bt->printKeys();
	bstData x;
	x = bt->search(20.0);
	std::cout << "x key: " << x.key << std::endl;
	delete bt;
	return 0;
}
