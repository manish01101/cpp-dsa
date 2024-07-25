#include "0.hpp"

class Solution {
public:
    void solve(node* root, int k, int& count, vector<int>& path) {
        //base case
        if (root == NULL) return;
        // add current node to path
        path.push_back(root->data);

        //left call
        solve(root->left, k, count, path);
        //right call
        solve(root->right, k, count, path);

        //check for K sum
        int size = path.size();
        int sum = 0;
        for (int i = size - 1; i >= 0; i--) {
            sum += path[i];
            if (sum == k)
                count++;
        }
        // backtrack
        path.pop_back();
    }
    int sumK(node* root, int k) {
        vector<int> path;
        int count = 0;
        solve(root, k, count, path);
        return count;
    }
};