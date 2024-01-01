#include<iostream>
#include<unordered_map>
#include<list>
#include<set>
#include<queue>
#include<vector>
using namespace std;

vector<vector<int> > printAdjacency(int n, int m, vector<vector<int> > &edges) {
    //ans array will store all adjacent nodes corresponding to index
    vector<int> ans[n];
    for(int i=0; i<m; i++) {
        int u = edges[i][0];
        int v = edges[i][1];

        ans[u].push_back(v);
        ans[v].push_back(u);
    }
    vector<vector<int>> adj(n);
    for(int i=0; i<n; i++) {
        adj[i].push_back(i);
        //entering neighbour
        for(int j=0; j<ans[i].size(); j++) {
            adj[i].push_back(ans[i][j]);
        }
    }
    return adj;
}