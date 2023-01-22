#include <iostream>
#include <string>
#include <stdlib.h>



template <typename keyType, typename bstData, typename bstNode> class binTree{
	public:
		bstNode *root;
		binTree();
		~binTree();
		int emptyCheck();
		void addNode(bstData inData);
		void propagate(bstNode *input, bstNode *curr);
		void printKeys();
		void printKeys(bstNode *curr);
		void destruct(bstNode *curr);
		void deleteKey(keyType val);
		bstNode *deleteKey(keyType val, bstNode *markedNode);
		bstData search(keyType val);
		bstNode *search(keyType val, bstNode *curr);

};

// constructor for the binary tree.
// initializes the root to be a null pointer
template <typename keyType, typename bstData, typename bstNode>
binTree<keyType, bstData, bstNode>::binTree(){
	root = NULL;
}
// destructor for the binary tree
template <typename keyType, typename bstData, typename bstNode>
binTree<keyType, bstData, bstNode>::~binTree(){
	destruct(root);
}
template <typename keyType, typename bstData, typename bstNode>
int binTree<keyType, bstData, bstNode>::emptyCheck(){
	if (root){
		return 1;
	}
	std::cout << "bst is empty" << std::endl;
	return 0;
}
// destruct - helper function to propagate through binTree 
// to clean destruct the tree. 
template <typename keyType, typename bstData, typename bstNode>
void binTree<keyType, bstData, bstNode>::destruct(bstNode *curr){
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
template <typename keyType, typename bstData, typename bstNode>
void binTree<keyType, bstData, bstNode>::propagate(bstNode *input, bstNode *curr){
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
template <typename keyType, typename bstData, typename bstNode>
void binTree<keyType, bstData, bstNode>::printKeys(){
	if(!emptyCheck()){return;}
	printKeys(root);
	std::cout << std::endl;
}
// prints the keys in order
template <typename keyType, typename bstData, typename bstNode>
void binTree<keyType, bstData, bstNode>::printKeys(bstNode *curr){
	// propagate left if possible
	if(!emptyCheck()){
		std::cout << "empty array" << std::endl;
		return;
	}
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
template <typename keyType, typename bstData, typename bstNode>
void binTree<keyType, bstData, bstNode>::addNode(bstData inputData){
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
template <typename keyType, typename bstData, typename bstNode>
bstData binTree<keyType, bstData, bstNode>::search(keyType val){
	bstNode *result;
	if(!emptyCheck()){
		std::cout << "FATAL: retrieving data from an uninitialized list." << std::endl;
		exit(1);
	}
	result = search(val, root);
	return result->data;
}
template <typename keyType, typename bstData, typename bstNode>
bstNode *binTree<keyType, bstData, bstNode>::search(keyType val, bstNode *curr){
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
template <typename keyType, typename bstData, typename bstNode>
void binTree<keyType, bstData, bstNode>::deleteKey(keyType val){
	if(!emptyCheck()){
		std::cout << "FATAL: deleting data from an uninitialized list." << std::endl;
		exit(1);
	}
	root = deleteKey(val, root);
}
template <typename keyType, typename bstData, typename bstNode>
bstNode *binTree<keyType, bstData, bstNode>::deleteKey(keyType val, bstNode *curr){
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
		if (curr->left && curr->right){
			bstNode *parent = curr;
			bstNode *successor = curr->right;
			while (successor->left){
				parent = successor;
				successor = successor->left;
			}
			curr->data = successor->data;
			if(curr->data.key < parent->data.key){
				parent->left = successor->right;
			}
			else{
				parent->right = successor->right;
			}
			delete successor;
		}
		else if (curr->left){
			curr->data = curr->left->data;
			bstNode *tempLeft = curr->left->left;
			bstNode *tempRight = curr->left->right;
			delete curr->left;
			curr->left = tempLeft;
			curr->right = tempRight;
		}
		else if (curr->right){
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


