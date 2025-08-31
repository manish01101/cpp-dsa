#include "0.hpp"

Node* solve(Node* root, int& k, int node) {
    // base case
    if (root == nullptr)
        return nullptr;
    if (root->data == node)
        return root;

    Node* leftAns = solve(root->left, k, node);
    Node* rightAns = solve(root->right, k, node);

    if (leftAns != nullptr && rightAns == nullptr) {
        k--;
        if (k <= 0) {
            k = INT_MAX; // ans lock
            return root;
        }
        return leftAns;
    }
    if (leftAns == nullptr && rightAns != nullptr) {
        k--;
        if (k <= 0) {
            k = INT_MAX; // ans lock
            return root;
        }
        return rightAns;
    }
    return nullptr;
}
int kthAncestor(Node* root, int k, int node) {
    Node* ans = solve(root, k, node);
    if (ans == nullptr || ans->data == node) return -1;
    else return ans->data;
}



class TreeAncestor {
    vector<int> parent;
public:
    TreeAncestor(int n, vector<int> &parent) {
        this->parent = parent;
    }
    int getKthAncestor(int node, int k) {
        while(k--) {
            node = parent[node];
        }
        return node;
    }
};

// optimised
class TreeAncestor {
    // using binary lifting
    vector<vector<int>> dp;
    int MAX_POWER;
public:
    TreeAncestor(int n, vector<int> &parent) {
        MAX_POWER = 0;
        while(1<<MAX_POWER <= n) 
            MAX_POWER++;
        dp = vector<vector<int>> (n, vector<int>(MAX_POWER, -1));
        // initializing 2^0-th ancestor i.e direct parent
        for(int i=0; i<n; ++i) {
            dp[i][0] = parent[i];
        }
        // precomputing 2^j-th ancestors for each node
        for(int j=1; j<MAX_POWER; ++j) {
            for(int i=0; i<n; ++i) {
                int prev = dp[i][j-1];
                if(prev != -1)
                    dp[i][j] = dp[prev][j-1];
            }
        }
    }
    int getKthAncestor(int node, int k) {
        for (int j = 0; j < MAX_POWER; ++j) {
            if (k & (1 << j)) {
                node = dp[node][j];
                if (node == -1) break;
            }
        }
        return node;
    }
};