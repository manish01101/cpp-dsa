#include "0.hpp"

/*
approach 1: ask each node where to get placed
approach 2: convert preorder to inorder by sorting
            make bst from inorder
approach 3: below
*/



Node* makeBST(vector<int>& pre, int mini, int maxi, int& index) {
    if (index >= pre.size())
        return nullptr;
    // check whether pre[index] lie in range or not
    // not lie return null
    if (pre[index] < mini || pre[index] > maxi)
        return nullptr;

    // lie in range
    Node* root = new Node(pre[index++]);
    root->left = makeBST(pre, mini, root->data, index);
    root->right = makeBST(pre, root->data, maxi, index);
    return root;
}
Node* preorderToBST(vector<int>& preorder) {
    int mini = INT_MIN;
    int maxi = INT_MAX;
    int index = 0;
    return makeBST(preorder, mini, maxi, index);
}