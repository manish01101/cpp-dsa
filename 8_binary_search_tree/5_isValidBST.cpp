#include "0.hpp"

/*
approach 1:
    inorder traversal -> is sorted -> T/F

appraoch 2:
    every nodes has some ranges where they lie
    -> for root ele, b/w int_min to int_max
    -> for left subtree, b/w int_min to root
    -> for right subree, b/w root to int_max
*/
bool isBST(Node* root, long min, long max) {
    if (root == nullptr)
        return true;
    if (root->data > min && root->data < max) {
        bool left = isBST(root->left, min, root->data);
        bool right = isBST(root->right, root->data, max);
        return left && right;
    }
    else {
        return false;
    }
}
bool isValidBST(Node* root) {
    return isBST(root, LONG_MIN, LONG_MAX);
}