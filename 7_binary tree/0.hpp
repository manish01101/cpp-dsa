#include<iostream>
#include<queue>
#include<stack>
#include<map>
#include<set>
#include<unordered_set>
#include<unordered_map>
using namespace std;

class node {
public:
    int data;
    node* left;
    node* right;

    node(int d) {
        this->data = d;
        this->left = NULL;
        this->right = NULL;
    }
};

class Node {
public:
    int data;
    Node* left;
    Node* right;
    
    Node(int data) :data(data), left(nullptr), right(nullptr) {}
};


int height(node* root) {
    //base case
    if (root == NULL) return 0;
    int left = height(root->left);
    int right = height(root->right);
    int ans = max(left, right) + 1;
    return ans;
}