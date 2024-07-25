#include "0.hpp"

/*
curr = root
while(curr != null) {
    if curr left exist
        pre = curr->left
        while(pre->right)
            pre = pre->right
        if(pre->right == null)
            pre->right = curr->right
            curr->right = curr->left
    curr = curr->right
}
*/

void flatten(node* root) {
    node* curr = root;
    while (curr != nullptr) {
        if (curr->left) {
            node* pre = curr->left;
            while (pre->right) {
                pre = pre->right;
            }
            // now pre->right == null
            pre->right = curr->right;
            curr->right = curr->left;
            // make left part null
            curr->left = nullptr;
        }
        curr = curr->right;
    }
}
