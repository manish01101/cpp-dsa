#include "0.hpp"

// max 
Node* maxi(Node* root) {
    Node* temp = root;
    while (temp->right != NULL)
        temp = temp->right;
    return temp;
}
// min 
Node* mini(Node* root) {
    Node* temp = root;
    while (temp->left != NULL)
        temp = temp->left;
    return temp;
}