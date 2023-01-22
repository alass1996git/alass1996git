#include "binTree.h"
#include <string>
#include <time.h>
#include <vector>
#include <algorithm>
#include <random>

typedef float userDefinedType;

// bstData 
// Adjust/add data fields as needed
// key is the key in which to sort the data
struct bstData{
	userDefinedType key;
};

// bstData - the data structure to contain contents of your data
// bstNode *left - left node down
// bstNode *right - right node down
struct bstNode{
	bstData data;
	bstNode *right;
	bstNode *left;
};


void addTo(binTree<userDefinedType, bstData, bstNode> *bt, userDefinedType val){
	bstData btData;
	btData.key = val;
	bt->addNode(btData);
}

void test(){
	srand(time(NULL));
	auto rng = std::default_random_engine {};
	for (int i = 0; i < 10; i++){
		binTree<userDefinedType, bstData, bstNode> *bt;
		bt = new binTree<userDefinedType, bstData, bstNode>;
		std::vector<float> myData;
		for(int j = 0; j < (int) (rand() % 200 + 1); j++){
			myData.push_back((float)( rand() % 1000000 + 1));
			addTo(bt, myData.data()[j]);
		}
		std::shuffle(std::begin(myData), std::end(myData), rng);
		int size = (int) myData.size();

		bt->printKeys();
		for(int j = 0; j < size; j++){
			bt->deleteKey(myData.back());	
			myData.pop_back();
			bt->printKeys();
		}	
		std::cout << "_______________________" << std::endl;
		delete bt;
	}
}

int main(){

	test();
	return 0;
}
