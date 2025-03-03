#include "0.hpp"

Node* insertIntoBST(Node* root, int d) {
    //base case
    if (root == nullptr) {
        root = new Node(d);
        return root;
    }
    if (d < root->data)
        root->left = insertIntoBST(root->left, d);
    else
        root->right = insertIntoBST(root->right, d);
    return root;
}
void takeInput(Node*& root) {
    int data;
    cin >> data;
    while (data != -1) {
        root = insertIntoBST(root, data);
        cin >> data;
    }
}
