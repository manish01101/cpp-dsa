#include "0.hpp"


Node* solve(int in[], int post[], int size, int& postOrderIndex, int inOrderStart, int inOrderEnd, map<int, int>& nodeToIndex) {
    // base case
    if (postOrderIndex < 0 || inOrderStart > inOrderEnd) {
        return nullptr;
    }

    int element = post[postOrderIndex--];
    Node* root = new Node(element);
    int position = nodeToIndex[element];

    // recursive call (right call first in postorder)
    root->right = solve(in, post, size, postOrderIndex, position + 1, inOrderEnd, nodeToIndex);
    root->left = solve(in, post, size, postOrderIndex, inOrderStart, position - 1, nodeToIndex);

    return root;
}
Node* buildTree(int in[], int post[], int n) {
    int postOrderIndex = n - 1;
    int inOrderStart = 0;
    int inOrderEnd = n - 1;
    // create nodes to index mapping
    map<int, int> nodeToIndex;
    for (int i = 0; i < n; i++) {
        nodeToIndex[in[i]] = i;
    }
    Node* ans = solve(in, post, n, postOrderIndex, inOrderStart, inOrderEnd, nodeToIndex);
    return ans;
}