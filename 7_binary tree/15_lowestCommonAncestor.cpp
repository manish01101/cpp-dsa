#include "0.hpp"

class Solution {
public:
    // Approach 1: Find path for n1 & n2, traverse from last and common element is LCA
    bool findPath(node* root, vector<node*>& path, int k) {
        if (root == NULL) return false;

        path.push_back(root);
        if (root->data == k) return true;

        if ((root->left && findPath(root->left, path, k)) ||
            (root->right && findPath(root->right, path, k)))
            return true;

        path.pop_back();
        return false;
    }

    node* lcaPathMethod(node* root, int n1, int n2) {
        vector<node*> path1, path2;
        if (!findPath(root, path1, n1) || !findPath(root, path2, n2))
            return NULL;

        int i;
        for (i = 0; i < path1.size() && i < path2.size(); i++) {
            if (path1[i] != path2[i])
                break;
        }
        return path1[i - 1];
    }

    // Approach 2: Recursive method
    node* lcaRecursive(node* root, int n1, int n2) {
        if (root == NULL) return NULL;
        if (root->data == n1 || root->data == n2) return root;

        node* leftLca = lcaRecursive(root->left, n1, n2);
        node* rightLca = lcaRecursive(root->right, n1, n2);

        if (leftLca && rightLca) return root;
        return (leftLca != NULL) ? leftLca : rightLca;
    }

    // Approach 3: Iterative using parent mapping
    node* lcaIterative(node* root, int n1, int n2) {
        if (root == NULL) return NULL;

        unordered_map<node*, node*> parent;
        unordered_set<node*> ancestors;
        queue<node*> q;
        parent[root] = NULL;
        q.push(root);

        while (!q.empty()) {
            node* curr = q.front(); q.pop();
            if (curr->left) {
                parent[curr->left] = curr;
                q.push(curr->left);
            }
            if (curr->right) {
                parent[curr->right] = curr;
                q.push(curr->right);
            }
        }

        node* current = NULL;

        // Traverse n1 to root and store ancestors
        for (current = findNode(root, n1); current != NULL; current = parent[current])
            ancestors.insert(current);

        // Traverse n2 to root, first match in ancestors is LCA
        for (current = findNode(root, n2); current != NULL; current = parent[current]) {
            if (ancestors.find(current) != ancestors.end())
                return current;
        }
        return NULL;
    }

    node* findNode(node* root, int val) {
        if (root == NULL) return NULL;
        if (root->data == val) return root;
        node* leftSearch = findNode(root->left, val);
        return leftSearch ? leftSearch : findNode(root->right, val);
    }
};

int main() {
    node* root = new node(1);
    root->left = new node(2);
    root->right = new node(3);
    root->left->left = new node(4);
    root->left->right = new node(5);
    root->right->left = new node(6);
    root->right->right = new node(7);

    Solution sol;
    node* lca1 = sol.lcaPathMethod(root, 4, 5);
    node* lca2 = sol.lcaRecursive(root, 4, 5);
    node* lca3 = sol.lcaIterative(root, 4, 5);

    cout << "LCA (Path Method): " << (lca1 ? lca1->data : -1) << endl;
    cout << "LCA (Recursive): " << (lca2 ? lca2->data : -1) << endl;
    cout << "LCA (Iterative): " << (lca3 ? lca3->data : -1) << endl;

    return 0;
}
/*
Instead of creating a parent map, we can find the start node and simultaneously run a BFS/DFS that explores both children and parent-like traversal.
The trick:
Treat the tree as an undirected graph.
Build adjacency list on the fly (like a graph of neighbors).
Then BFS from the start node.

✅ Approach (No Parent Map)
Build an adjacency list (unordered_map<int, vector<int>> graph) from the binary tree:
Each edge is bidirectional (u ↔ v).
That way, you don't need an explicit parent map.
BFS starting from the node start.
Track visited nodes to prevent cycles.
Each BFS level adds 1 to time.
*/

class Solution {
    void buildGraph(TreeNode* root, unordered_map<int, vector<int>>& graph) {
        if (!root) return;

        if (root->left) {
            graph[root->val].push_back(root->left->val);
            graph[root->left->val].push_back(root->val);
            buildGraph(root->left, graph);
        }
        if (root->right) {
            graph[root->val].push_back(root->right->val);
            graph[root->right->val].push_back(root->val);
            buildGraph(root->right, graph);
        }
    }

public:
    int amountOfTime(TreeNode* root, int start) {
        // Step 1: Build adjacency list
        unordered_map<int, vector<int>> graph;
        buildGraph(root, graph);

        // Step 2: BFS from start
        queue<int> q;
        unordered_set<int> visited;

        q.push(start);
        visited.insert(start);

        int time = -1; // because last level does not spread
        while (!q.empty()) {
            int size = q.size();
            ++time; // each level takes 1 unit time

            for (int i = 0; i < size; i++) {
                int node = q.front();
                q.pop();

                for (int nei : graph[node]) {
                    if (!visited.count(nei)) {
                        visited.insert(nei);
                        q.push(nei);
                    }
                }
            }
        }
        return time;
    }
};
