#include "0.hpp"


void inorder(Node* root, vector<int>& in) {
    if (root == nullptr)
        return;
    inorder(root->left, in);
    in.push_back(root->data);
    inorder(root->right, in);
}
Node* flat(Node* root) {
    // make inorder vector
    vector<int> in;
    inorder(root, in);
    int n = in.size();
    // create node for first ele
    Node* newRoot = new Node(in[0]);
    Node* curr = newRoot;
    // node creation for rest ele
    for (int i = 1; i < n; i++) {
        Node* newNode = new Node(in[1]);
        curr->left = nullptr;
        curr->right = newNode;
        curr = newNode; // increment curr
    }
    // make last node to nullptr
    curr->left = nullptr;
    curr->right = nullptr;

    return newRoot;
}