#include <iostream>
#include <string>
#include <stdlib.h>

typedef float keyType;

// bstData 
// Adjust/add data fields as needed
// key is the key in which to sort the data
struct bstData{
	keyType key;
};

// bstData - the data structure to contain contents of your data
// bstNode *left - left node down
// bstNode *right - right node down
struct bstNode{
	bstData data;
	bstNode *right;
	bstNode *left;
};

class binTree{
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
