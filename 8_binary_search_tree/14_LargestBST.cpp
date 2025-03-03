#include "0.hpp"
/*
approach 1;
for each node check whether make valid bst if yes store size
isBST  tc: O(n2)

for valid bst
    -> check for left subtree
    -> check for right subtree
    -> max of left < root->data < min of right

approach 2: tc: O(n)
*/
// tc - O(n)
struct info {
    int maxi;
    int mini;
    bool isBST;
    int size;
} typedef info;

info solve(Node* root, int& ans) {
    //base case
    if (root == nullptr) {
        return { INT_MIN, INT_MAX, true, 0 };
    }

    info left = solve(root->left, ans);
    info right = solve(root->right, ans);

    info currNode;
    currNode.size = left.size + right.size + 1;
    currNode.maxi = max(root->data, right.maxi);
    currNode.mini = min(root->data, left.mini);
    if (left.isBST && right.isBST && (root->data > left.maxi && root->data < right.mini)) {
        currNode.isBST = true;
    }
    else {
        currNode.isBST = false;
    }

    // answer update
    if (currNode.isBST) {
        ans = max(ans, currNode.size);
    }
    return currNode;
}


int largestBST(Node* root) {
    int maxSize = 0;
    info temp = solve(root, maxSize);
    return maxSize;
}