#include "0.hpp"

//recursive way TC=O(logn) SC = O(n)
bool searchInBST(Node* root, int x) {
    //base case
    if (root == nullptr) return false;

    if (root->data == x) return true;
    if (root->data > x)
        return searchInBST(root->left, x);
    else
        return searchInBST(root->right, x);
}

//iterative way TC=O(logn) SC = O(1)
bool searchInBST(Node* root, int x) {

    Node* temp = root;

    while (temp != nullptr) {
        if (temp->data == x) return true;
        if (temp->data > x) temp = temp->left;
        else temp = temp->right;
    }
    return false;
}