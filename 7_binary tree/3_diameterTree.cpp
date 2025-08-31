#pragma once
#include "0.hpp"
/*
diameter: longest path b/w any 2 end nodes
*/

int diameter(node* root) {  //T.C - O(n2)
    if (root == NULL) return 0;
    int op1 = diameter(root->left);
    int op2 = diameter(root->right);
    int op3 = height(root->left) + height(root->right);
    int ans = max(op1, max(op2, op3));
    return ans;
}
//opmising above diameter fn
pair<int, int> diameterHei(node* root) { // <dia, height>
    //base case
    if (root == NULL) {
        pair<int, int> p = make_pair(0, 0);
        return p;
    }
    pair<int, int> left = diameterHei(root->left);
    pair<int, int> right = diameterHei(root->right);

    int op1 = left.first;
    int op2 = right.first;
    int op3 = left.second + right.second + 1;

    pair<int, int> ans;
    ans.first = max(op1, max(op2, op3)); //diameter
    ans.second = max(left.second, right.second) + 1; //height
    return ans;
}
// t.c = O(n)
int diameterOptimised(node* root) {
    return diameterHei(root).first;
}

// tc=O(n)
class Solution {
    int diameter = 0;
    int height(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }

        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

        int currentDiameter = leftHeight + rightHeight;
        diameter = max(diameter, currentDiameter);
        return 1 + max(leftHeight, rightHeight);
    }

public:
    int diameterOfBinaryTree(TreeNode* root) {
        height(root);
        return diameter;
    }
};
