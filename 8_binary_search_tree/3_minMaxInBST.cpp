#include "0.hpp"

// max 
Node* maxi(Node* root) {
    Node* temp = root;
    while (temp->right != nullptr)
        temp = temp->right;
    return temp;
}
// min 
Node* mini(Node* root) {
    Node* temp = root;
    while (temp->left != nullptr)
        temp = temp->left;
    return temp;
}