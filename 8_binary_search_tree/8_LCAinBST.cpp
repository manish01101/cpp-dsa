#include "0.hpp"

/*
a > root && b > root -> a&b is in right part
a < root && b < root => a&b is in left part
a < root && b > root or a > root && b < root => ans is root
*/
// recursive tc, sc o(n) 
Node* lcaInBst(Node* root, Node* a, Node* b) {
    if (root == nullptr) return root;

    if (a->data > root->data && b->data > root->data) {
        return lcaInBst(root->right, a, b);
    }
    if (a->data < root->data && b->data < root->data) {
        return lcaInBst(root->left, a, b);
    }
    // rest case
    return root;
}

// iterative tc: O(n) sc: o(1)
Node* lcaInBstRec(Node* root, Node* a, Node* b) {
    if (root == nullptr) return root;
    while (root != nullptr) {
        if (a->data > root->data && b->data > root->data) {
            root = root->right;
        }
        else if (a->data < root->data && b->data < root->data) {
            root = root->left;
        }
        else {
            return root;
        }
    }
}