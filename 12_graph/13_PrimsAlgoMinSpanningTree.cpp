#include<iostream>
#include<unordered_map>
#include<list>
#include<set>
#include<vector>
#include<queue>
#include<limits.h>
using namespace std;
/*
if graph converted into tree, it has n nodes and n-1 edges and every node is reacheable by every other node
*/

// main fn
vector<pair<pair<int, int>, int>> calculatePrimsMST(int n, int m, vector<pair<pair<int, int>, int>>& g) {
    // create adj list
    unordered_map<int, list<pair<int, int>>> adj;
    for (int i = 0; i < g.size(); i++) {
        int u = g[i].first.first;
        int v = g[i].first.second;
        int w = g[i].second;
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }
    // make needed three data structure
    vector<int> weight(n + 1, INT_MAX); // n+1=>for fetching node with index 1-based indexing
    vector<bool> isNodeInMstVisited(n + 1, false);
    vector<int> parent(n + 1, -1);

    // starting the algo 
    int src = 1;
    weight[src] = 0;
    parent[src] = -1;

    for (int i = 1; i < n; i++) {
        // STEP 1: find node with min weight
        int miniWeight = INT_MAX;
        int node;
        for (int v = 1; v <= n; v++) {
            if (isNodeInMstVisited[v] == false && weight[v] < miniWeight) {
                node = v;
                miniWeight = weight[v];
            }
        }
        // STEP 2: mark min node as true;
        isNodeInMstVisited[node] = true;
        // STEP 3: check its adjacent nodes
        for (auto it : adj[node]) {
            int neighbourNode = it.first;
            int neighbourWeight = it.second;
            if (isNodeInMstVisited[neighbourNode] == false && neighbourWeight < weight[neighbourNode]) {
                parent[neighbourNode] = node;
                weight[neighbourNode] = neighbourWeight;
            }
        }
    }
    // ans -> mini spanning tree
    vector<pair<pair<int, int>, int>> result;
    for (int i = 2; i <= n; i++) {
        result.push_back({ {parent[i], i}, weight[i] });
    }
    return result;
}






vector<pair<pair<int, int>, int>> calculatePrimsMST(int n, int m, vector<pair<pair<int, int>, int>>& g) {
    // create adj list
    unordered_map<int, list<pair<int, int>>> adj;
    for (int i = 0; i < g.size(); i++) {
        int u = g[i].first.first;
        int v = g[i].first.second;
        int w = g[i].second;
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }
    // make needed three data structure
    vector<int> weight(n + 1, INT_MAX); // n+1 for 1 based indexing
    vector<bool> isNodeInMstVisited(n + 1, false);
    vector<int> parent(n + 1, -1);
    // pair<weigth, node>
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;

    // starting the algo 
    int src = 1;
    weight[src] = 0;
    parent[src] = -1;

    pq.push({ weight[src], src });

    while (!pq.empty()) {
        // STEP 1: find node with min weight
        int node = pq.top().second;
        int nodeWeight = pq.top().first;
        pq.pop();

        // STEP 2: mark min weight node as visited
        isNodeInMstVisited[node] = true;

        // STEP 3: go for adjacent node
        for (auto it : adj[node]) {
            int neighbourNode = it.first;
            int neighbourWeight = it.second;

            if (isNodeInMstVisited[neighbourNode] == false && neighbourWeight < weight[neighbourNode]) {
                parent[neighbourNode] = node;
                weight[neighbourNode] = neighbourWeight;
                pq.push({ weight[neighbourNode], neighbourNode });
            }
        }
    }

    // ans -> mini spanning tree
    vector<pair<pair<int, int>, int>> result;
    for (int i = 2; i <= n; i++) {
        result.push_back({ {parent[i], i}, weight[i] });
    }
    return result;
}
