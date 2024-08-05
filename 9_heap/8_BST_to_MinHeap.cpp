#include<iostream>
#include<vector>
#include<queue>
using namespace std;
class Node {
public:
	int data;
	Node* left;
	Node* right;
	Node(int data) {
		this->data = data;
		this->left = nullptr;
		this->right = nullptr;
	}
};

/*
bst is already CBT so no change in structure
->find inorder
->replace data using preorder (NLR)
*/

void inorder(Node* root, vector<int>& in) {
	if (root == nullptr)
		return;
	inorder(root->left, in);
	in.push_back(root->data);
	inorder(root->right, in);
}
void replaceData(Node* root, vector<int>& in, int& i) {
	if (root == nullptr)
		return;
	root->data = in[i++];
	replaceData(root->left, in, i);
	replaceData(root->right, in, i);
}

void BST_To_MinHeap(Node* root) {
	// make inorder arr
	vector<int> in;
	inorder(root, in);
	int i = 0;
	replaceData(root, in, i);
}