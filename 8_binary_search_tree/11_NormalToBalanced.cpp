#include "0.hpp"


void inorder(Node* root, vector<int>& in) {
    if (root == nullptr)
        return;
    inorder(root->left, in);
    in.push_back(root->data);
    inorder(root->right, in);
}
Node* inorderToBst(int start, int end, vector<int>& in) {
    if (start > end)
        return nullptr;
    int mid = (start + end) / 2;
    Node* root = new Node(in[mid]);
    root->left = inorderToBst(start, mid - 1, in);
    root->right = inorderToBst(mid + 1, end, in);
    return root;
}
Node* balanceBst(Node* root) {
    // make inorder vector
    vector<int> in;
    inorder(root, in);

    int start = 0, end = in.size() - 1;
    return inorderToBst(start, end, in);
}