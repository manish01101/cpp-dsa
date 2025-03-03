#include "0.hpp"
Node* minVal(Node* root) {
    Node* temp = root;
    while (temp->left != nullptr) {
        temp = temp->left;
    }
    return temp;
}
Node* deleteFromBST(Node* root, int val) {
    //base case
    if (root == nullptr) return root;

    if (root->data == val) {
        // 0 child
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }
        // 1 child
        //left child
        if (root->left != nullptr && root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        //right child
        if (root->left == nullptr && root->left != nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }

        // 2 child
        if (root->left != nullptr && root->right != nullptr) {
            int mini = minVal(root->right)->data;
            root->data = mini;
            root->right = deleteFromBST(root->right, mini);
            return root;
        }
    }

    else if (root->data > val) {
        //left part me jao
        root->left = deleteFromBST(root->left, val);
        return root;
    }
    else {
        //right part me jao
        root->right = deleteFromBST(root->right, val);
        return root;
    }
}