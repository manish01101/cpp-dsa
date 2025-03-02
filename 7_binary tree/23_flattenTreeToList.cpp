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
// flattening a binary tree into a linked list in preorder traversal order (root → left → right).
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

//postorder approach (left → right → root).
void flatten(node* root) {
    if (!root) return;
    
    flatten(root->left);
    flatten(root->right);
    
    if (root->left) {
        node* temp = root->right;
        root->right = root->left;
        root->left = nullptr;
        
        node* last = root->right;
        while (last->right) {
            last = last->right;
        }
        last->right = temp;
    }
}
