#include "0.hpp"

// recursive sol
int solve(Node* root, int& i, int k) {
    //base case
    if (root == nullptr) {
        return -1;
    }
    //L
    int left = solve(root->left, i, k);
    if (left != -1) return left;

    //N
    i++;
    if (i == k) return root->data;

    //R
    return solve(root->right, i, k);
}

int kthSmallest(Node* root, int k) {
    int i = 0;
    int ans = solve(root, i, k);
    return ans;
}



// morris traversal
int kthSmallest(Node* root, int k) {
    if (root == nullptr) return -1;
    int i = 0;
    int ans = -1;
    Node* curr = root;
    while (curr != nullptr) {
        if (curr->left == nullptr) {
            i++;
            if (i == k) {
                ans = curr->data;
            }
            curr = curr->right;
        }
        else {
            Node* pred = curr->left;
            while (pred->right != nullptr && pred->right != curr) {
                pred = pred->right;
            }
            if (pred->right == nullptr) {
                pred->right = curr;
                curr = curr->left;
            }
            else {
                pred->right = nullptr;
                i++;
                if (i == k) {
                    ans = curr->data;
                }
                curr = curr->right;
            }
        }
    }
    return ans;
}