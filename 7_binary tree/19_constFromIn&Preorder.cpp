#include "0.hpp"


/*
approach
-> take index ele as root ele of pre
-> find root ele position
-> root->left call (inorder start, position-1)
-> root->right call (position+1, inorder end)
*/
int findPosition(int in[], int element, int size) {
    for (int i = 0; i < size; i++) {
        if (in[i] == element) {
            return i;
        }
    }
    return -1;
}
Node* solve(int in[], int pre[], int& preOrderIndex, int inOrderStart, int inOrderEnd, int size) {
    // base case
    if (preOrderIndex >= size || inOrderStart > inOrderEnd) {
        return nullptr;
    }
    int element = pre[preOrderIndex++];
    Node* root = new Node(element);
    int position = findPosition(in, element, size);

    // recursive call
    root->left = solve(in, pre, preOrderIndex, inOrderStart, position - 1, size);
    root->right = solve(in, pre, preOrderIndex, position + 1, inOrderEnd, size);

    return root;
}
Node* buildTree(int in[], int pre[], int n) {
    int preOrderIndex = 0;
    int inOrderStart = 0;
    int inOrderEnd = n - 1;
    Node* ans = solve(in, pre, preOrderIndex, inOrderStart, inOrderEnd, n);
    return ans;
}


// create a map for optimising findPosition 

Node* solve2(int in[], int pre[], int& preOrderIndex, int inOrderStart, int inOrderEnd, int size, map<int, int>& nodeToIndex) {
    // base case
    if (preOrderIndex >= size || inOrderStart > inOrderEnd) {
        return nullptr;
    }

    int element = pre[preOrderIndex++];
    Node* root = new Node(element);
    int position = nodeToIndex[element];

    // recursive call (left call first in preorder)
    root->left = solve2(in, pre, preOrderIndex, inOrderStart, position - 1, size, nodeToIndex);
    root->right = solve2(in, pre, preOrderIndex, position + 1, inOrderEnd, size, nodeToIndex);

    return root;
}
Node* buildTree(int in[], int pre[], int n) {
    int preOrderIndex = 0;
    int inOrderStart = 0;
    int inOrderEnd = n - 1;
    // create mapping of inorder arr element with index
    map<int, int> nodeToIndex;
    for (int i = 0; i < n; i++) {
        nodeToIndex[in[i]] = i;
    }
    Node* ans = solve2(in, pre, preOrderIndex, inOrderStart, inOrderEnd, n, nodeToIndex);
    return ans;
}