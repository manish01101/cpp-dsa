#include "0.hpp"\


pair<int, int> predecessorSuccessor2(Node* root, int key) {
    // step 1: find key
    Node* temp = root;
    int pred = -1;
    int succ = -1;
    while (temp->data != key) {
        if (temp->data > key) { // search in left part
            succ = temp->data; //candidate for succ
            temp = temp->left;
        }
        if (temp->data < key) { // search in right part
            pred = temp->data; // candidate for pred
            temp = temp->right;
        }
    }
    // now we have temp->data == key
    // step 2: find pred and succ
    // predecessor
    Node* leftTree = temp->left;
    while (leftTree != nullptr) {
        pred = leftTree->data;
        leftTree = leftTree->right;
    }
    // successor
    Node* rightTree = temp->right;
    while (rightTree != nullptr) {
        succ = rightTree->data;
        rightTree = rightTree->left;
    }
    return { pred, succ };
}