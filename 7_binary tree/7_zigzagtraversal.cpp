#pragma once
#include "0.hpp"


// zig zag tree traversal
vector<int> zigzagTraversal(node* root) {
    vector<int> result;
    if (root == NULL) return result;

    queue<node*> q;
    q.push(root);

    bool leftToRight = true;

    while (!q.empty()) {
        int size = q.size();
        vector<int> ans(size);
        //level process
        for (int i = 0; i < size; i++) {
            node* frontNode = q.front();
            q.pop();
            //normal / reverse insert
            int index = leftToRight ? i : size - i - 1;
            ans[index] = frontNode->data;

            if (frontNode->left)
                q.push(frontNode->left);
            if (frontNode->right)
                q.push(frontNode->right);
        }
        //direction change
        leftToRight = !leftToRight;
        for (auto i : ans) {
            result.push_back(i);
        }
    }
    return result;
}