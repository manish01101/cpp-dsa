#include "0.hpp"


void inorder(Node* root, vector<int>& in) {
    if (root == nullptr)
        return;
    inorder(root->left, in);
    in.push_back(root->data);
    inorder(root->right, in);
}
Node* flat(Node* root) {
    // make inorder vector
    vector<int> in;
    inorder(root, in);
    int n = in.size();
    // create node for first ele
    Node* newRoot = new Node(in[0]);
    Node* curr = newRoot;
    // node creation for rest ele
    for (int i = 1; i < n; i++) {
        Node* newNode = new Node(in[i]);
        curr->left = nullptr;
        curr->right = newNode;
        curr = newNode; // increment curr
    }
    // make last node to nullptr
    curr->left = nullptr;
    curr->right = nullptr;

    return newRoot;
}

// morris traversal for inorder traversal (used to flatten a bst)
void flattenToSortedList(node* root) {
    node* curr = root;
    
    while (curr != nullptr) {
        if (curr->left) {
            // Find the rightmost node of the left subtree
            node* pre = curr->left;
            while (pre->right) {
                pre = pre->right;
            }
            
            // Connect the rightmost node of the left subtree to the current node's right
            pre->right = curr->right;
            
            // Move the left subtree to the right of the current node
            curr->right = curr->left;
            curr->left = nullptr;
        }
        
        // Move to the next node
        curr = curr->right;
    }
}


// recursive approach
node* prev = nullptr;
void flattenBST(node* root) {
    if (!root) return;

    flattenBST(root->left);  // Left subtree
    root->left = nullptr;     // Remove left pointer
    if (prev) prev->right = root;
    prev = root;
    flattenBST(root->right); // Right subtree
}

class Solution {
  public:
    Node* prev = nullptr;
    Node* ans = nullptr;
    bool flag = true;
    Node *flattenBST(Node *root) {
        if(!root) return nullptr;
        
        flattenBST(root->left);
        root->left = nullptr;
        
        if(prev) prev->right = root;
        if(flag) {
            ans = root;
            flag = false;
        }
        prev = root;
        
        flattenBST(root->right);
        return ans;
    }
};