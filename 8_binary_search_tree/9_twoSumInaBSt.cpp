#include "0.hpp"


void inorder(Node* root, vector<int>& in) {
    if (root == nullptr) {
        return;
    }
    inorder(root->left, in);
    in.push_back(root->data);
    inorder(root->right, in);
}
bool twoSumInBST(Node* root, int target) {
    vector<int> in;
    inorder(root, in);
    // here we use two pointer approach to find the target sum
    int i = 0;
    int j = in.size() - 1;
    while (i < j) {
        int sum = in[i] + in[j];
        if (sum == target) {
            return true;
        }
        else if (sum > target) {
            j--;
        }
        else {
            i++;
        }
    }
    return false;
}