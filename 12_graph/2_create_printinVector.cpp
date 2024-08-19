#include<iostream>
#include<unordered_map>
#include<list>
#include<set>
#include<queue>
#include<vector>
using namespace std;


vector<vector<int>> printAdj(int node, int edge, vector<vector<int>>& edges) {
    //ans array will store all adjacent nodes corresponding to index
    vector<int> ans[node];
    for (int i = 0; i < edge; i++) {
        int u = edges[i][0];
        int v = edges[i][1];

        ans[u].push_back(v);
        ans[v].push_back(u);
    }
    vector<vector<int>> adj(node);
    for (int i = 0; i < node; i++) {
        adj[i].push_back(i);
        //entering neighbour
        for (int j = 0; j < ans[i].size(); j++) {
            adj[i].push_back(ans[i][j]);
        }
    }
    return adj;
}
