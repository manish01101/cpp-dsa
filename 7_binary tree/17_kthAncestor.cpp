#include "0.hpp"

Node* solve(Node* root, int& k, int node) {
    // base case
    if (root == nullptr)
        return nullptr;
    if (root->data == node)
        return root;

    Node* leftAns = solve(root->left, k, node);
    Node* rightAns = solve(root->right, k, node);

    if (leftAns != nullptr && rightAns == nullptr) {
        k--;
        if (k <= 0) {
            k = INT_MAX; // ans lock
            return root;
        }
        return leftAns;
    }
    if (leftAns == nullptr && rightAns != nullptr) {
        k--;
        if (k <= 0) {
            k = INT_MAX; // ans lock
            return root;
        }
        return rightAns;
    }
    return nullptr;
}
int kthAncestor(Node* root, int k, int node) {
    Node* ans = solve(root, k, node);
    if (ans == nullptr || ans->data == node) return -1;
    else return ans->data;
}
