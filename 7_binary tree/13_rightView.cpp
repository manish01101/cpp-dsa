#pragma once
#include "0.hpp"

//right view of binary tree
void solve(node* root, vector<int>& ans, int level) {
    //base case
    if (root == NULL) return;

    //we entered into a new level
    if (level == ans.size())
        ans.push_back(root->data);

    solve(root->right, ans, level + 1);
    solve(root->left, ans, level + 1);
}
vector<int> rightView(node* root) {
    vector<int> ans;
    solve(root, ans, 0);
    return ans;
}