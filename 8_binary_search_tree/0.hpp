#include<iostream>
#include<map>
#include<stack>
#include<algorithm>
#include<queue>
using namespace std;

class Node {
public:
	int data;
	Node* left;
	Node* right;
	Node(int d) { // constructor
		this->data = d;
		this->left = NULL;
		this->right = NULL;
	}
};