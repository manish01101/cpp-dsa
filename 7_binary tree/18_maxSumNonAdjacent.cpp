#include "0.hpp"

/*
pair<a, b>
a = maxsum by including nodes at current level
b = maxsum by excluding nodes at current level

a =
*/

pair<int, int> solve(Node* root) {
    // base case
    if (root == nullptr) {
        pair<int, int> p = make_pair(0, 0);
        return p;
    }
    pair<int, int> left = solve(root->left);
    pair<int, int> right = solve(root->right);

    pair<int, int> result; // pair<include, exclude>
    // include = root->data + child's exclude part
    result.first = root->data + left.second + right.second;
    // exlcude
    result.second = max(left.first, left.second) + max(right.first, right.second);

    return result;
}

int getMaxSum(Node* root) {
    pair<int, int> ans = solve(root);
    return max(ans.first, ans.second);
}