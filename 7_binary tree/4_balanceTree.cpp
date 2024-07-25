#pragma once
#include "0.hpp"

bool isBalanced(node* root) { //T.C = O(n2)
    //base case
    if (root == NULL) return true;

    bool left = isBalanced(root->left);
    bool right = isBalanced(root->right);

    bool diff = abs(height(root->left) - height(root->right)) <= 1;

    if (left && right && diff) return true;
    else return false;
}
//optimising above fn - TC = O(n)
pair<bool, int> isBalancedOpt(node* root) {
    //base case
    if (root == NULL) {
        pair<bool, int> p = make_pair(true, 0);
        return p;
    }
    pair<bool, int> left = isBalancedOpt(root->left);
    pair<bool, int> right = isBalancedOpt(root->right);

    bool leftAns = left.first;
    bool rightAns = right.first;

    bool diff = abs(left.second - right.second) <= 1;

    pair<bool, int> ans;
    ans.second = max(left.second, right.second) + 1;

    if (leftAns && rightAns && diff) {
        ans.first = true;
    }
    else ans.first = false;
    return ans;
}
bool isBalancedAns(node* root) {
    return isBalancedOpt(root).first;
}