#include<iostream>
#include<unordered_map>
#include<list>
#include<set>
#include<stack>
#include<algorithm>
#include<vector>
#include<limits.h>
using namespace std;

/*
kosaraju algo used to find strongly connected component
strongly connected component: if we start from any node of a component, we can visit every node of that component
*/

void dfs(int node, unordered_map<int, bool>& vis, stack<int>& st, unordered_map<int, list<int>>& adj) {
    vis[node] = true;
    for (auto nbr : adj[node]) {
        if (!vis[nbr]) {
            dfs(nbr, vis, st, adj);
        }
    }
    // topo logic at return push to stack
    st.push(node);
}

void revDfs(int node, unordered_map<int, bool>& vis, unordered_map<int, list<int>>& adj) {
    vis[node] = true;
    for (auto nbr : adj[node]) {
        if (!vis[nbr]) {
            revDfs(nbr, vis, adj);
        }
    }
}

int stronglyConnectedComponents(int v, vector<vector<int>>& edges) {
    // adj list
    unordered_map<int, list<int>> adj;
    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        adj[u].push_back(v);
    }

    // step 1: topo sort
    stack<int> st;
    unordered_map<int, bool> vis;
    for (int i = 0; i < v; i++) {
        if (!vis[i]) {
            dfs(i, vis, st, adj);
        }
    }

    // step 2: create a transpose graph(means reverse edge direction) as stack returns node in reverse order
    unordered_map<int, list<int>> transpose;
    for (int i = 0; i < v; i++) {
        for (auto nbr : adj[i]) {
            vis[i] = 0; // as it is change in topo sort
            transpose[nbr].push_back(i);
        }
    }

    // step 3: call dfs using above ordering
    int count = 0;
    while (!st.empty()) {
        int top = st.top();
        st.pop();
        if (!vis[top]) {
            count++;
            revDfs(top, vis, transpose);
        }
    }
    return count;
}