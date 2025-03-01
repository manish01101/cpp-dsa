#include "0.hpp"

// morris Traversal for inorder traversal
void morrisTraversal(node* root) { // TC: O(N) sc: o(1)
    if (root == nullptr) return;

    node* curr = root;
    while (curr != nullptr) {
        if (curr->left == nullptr) {
            cout << curr->data << " ";
            curr = curr->right;
        }
        else {
            // find the inorder predecessor of curr
            node* pre = curr->left;
            while (pre->right != nullptr && pre->right != curr) {
                pre = pre->right;
            }
            // make curr as the right child of its inorder predecessor i.e link creation
            if (pre->right == nullptr) {
                pre->right = curr;
                curr = curr->left;
            }
            // removal of link
            else {
                pre->right == nullptr;
                cout << curr->data << " ";
                curr = curr->right;
            }
        }
    }
}