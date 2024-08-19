#include<iostream>
#include<unordered_map>
#include<list>
#include<set>
#include<algorithm>
#include<vector>
#include<limits.h>
using namespace std;

/*
bridge -> that edge, which increases the no. of components after removing it.
*/

void dfs(int node, int parent, int& timer, vector<int>& discoveryTime, vector<int>& earliestTime, vector<vector<int>>& result, unordered_map<int, list<int>> adj, unordered_map<int, bool>& isVisited) {

    isVisited[node] = true;
    discoveryTime[node] = earliestTime[node] = timer++;

    for (auto neighbour : adj[node]) {
        if (neighbour == parent)
            continue;
        if (!isVisited[neighbour]) {
            dfs(neighbour, node, timer, discoveryTime, earliestTime, result, adj, isVisited);

            earliestTime[node] = min(earliestTime[node], earliestTime[neighbour]);
            // check edge is bridge
            if (earliestTime[neighbour] > discoveryTime[node]) {
                vector<int> ans;
                ans.push_back(node);
                ans.push_back(neighbour);
                result.push_back(ans);
            }
        }
        else {
            // node already visited and not parent
            // back edge
            earliestTime[node] = min(earliestTime[node], discoveryTime[neighbour]);
        }
    }
}


// main fn
vector<vector<int>> findBridges(vector<vector<int>>& edges, int v, int e) {
    // adj list
    unordered_map<int, list<int>> adj;
    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int timer = 0;
    vector<int> discoveryTime(v, -1); // track node visited when
    vector<int> earliestTime(v, -1); // earliest possible time to reach node
    int parent = -1; // to track parent
    unordered_map<int, bool> isVisited;

    vector<vector<int>> result;
    // dfs
    for (int i = 0; i < v; i++) {
        if (!isVisited[i]) {
            dfs(i, parent, timer, discoveryTime, earliestTime, result, adj, isVisited);
        }
    }
    return result;
}