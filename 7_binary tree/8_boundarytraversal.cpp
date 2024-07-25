#pragma once
#include "0.hpp"

//boundary traversal of binary tree
void traverseLeft(node* root, vector<int>& ans) {
    //base case
    if ((root == NULL) || (root->left == NULL && root->right == NULL)) return;

    ans.push_back(root->data);

    if (root->left)
        traverseLeft(root->left, ans);
    else
        traverseLeft(root->right, ans);
}
void  traverseLeaf(node* root, vector<int>& ans) {
    //base case
    if (root == NULL) return;
    if (root->left == NULL && root->right == NULL) { // leaf node
        ans.push_back(root->data);
        return;
    }
    traverseLeaf(root->left, ans);
    traverseLeaf(root->right, ans);
}
void traverseRight(node* root, vector<int>& ans) {
    //base case
    if ((root == NULL) || (root->left == NULL && root->right == NULL)) return;

    if (root->right)
        traverseRight(root->right, ans);
    else
        traverseRight(root->left, ans);

    // store node data while returning
    ans.push_back(root->data);
}

// main fn
vector<int> boundary(node* root) {
    vector<int> ans;
    if (root == NULL) return ans;

    ans.push_back(root->data);

    //left part print / store
    traverseLeft(root->left, ans);
    //traverse leaf nodes
    traverseLeaf(root->left, ans);
    traverseLeaf(root->right, ans);
    //traverse right part
    traverseRight(root->right, ans);

    return ans;
}