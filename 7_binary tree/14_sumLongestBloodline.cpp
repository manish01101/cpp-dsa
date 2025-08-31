#include "0.hpp"

class Solution { // root to leaf node
public:
    void solve(node* root, int sum, int& maxSum, int len, int& maxLen) {
        //base case
        if (root == NULL) {
            if (len > maxLen) {
                maxLen = len;
                maxSum = sum;
            }
            else if (len == maxLen) {
                maxSum = max(sum, maxSum);
            }
            return;
        }
        sum += root->data;
        solve(root->left, sum, maxSum, len + 1, maxLen);
        solve(root->right, sum, maxSum, len + 1, maxLen);
    }

    int sumOfLongRootToLeafPath(node* root) {
        int len = 0;
        int maxLen = 0;

        int sum = 0;
        int maxSum = INT_MIN;

        solve(root, sum, maxSum, len, maxLen);
        return maxSum;
    }
};


class FromAnyNode {
    int findMaxPathDown(TreeNode* root, int& ans) {
        if (root == nullptr)
            return 0;

        int leftMax = findMaxPathDown(root->left, ans);
        int rightMax = findMaxPathDown(root->right, ans);

        // one side path starting at this root
        int maxSinglePath = max(max(leftMax, rightMax) + root->val, root->val);

        // any path passing through this root
        int maxTopPath = max(maxSinglePath, leftMax + rightMax + root->val);

        ans = max(ans, maxTopPath);
        return maxSinglePath;
    }
public:
    int maxPathSum(TreeNode* root) {
        int ans = INT_MIN;
        findMaxPathDown(root, ans);
        return ans;
    }
};