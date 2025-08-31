#include<iostream>
#include<unordered_map>
#include<list>
#include<set>
#include<algorithm>
#include<vector>
#include<limits.h>
using namespace std;

/*
articulation point -> node upon removal, graph divided into two or more component
leaf nodes are not articulation points,

0 - 1
|   |
3 - 2
So in a cycle:
No edge is a bridge
No node is an articulation point

tc & sc : O(V + E)
*/

void dfs(int node, int parent, vector<int>& discoveryTime, vector<int>& earliestTime, unordered_map<int, bool>& isVisited, unordered_map<int, list<int>>& adj, vector<bool>& isAP, int& timer) {

    isVisited[node] = true;
    discoveryTime[node] = earliestTime[node] = timer++;
    int child = 0;

    for (auto neighbour : adj[node]) {
        if (neighbour == parent) {
            continue;
        }
        if (!isVisited[neighbour]) {
            dfs(neighbour, node, discoveryTime, earliestTime, isVisited, adj, isAP, timer);
            // update earliest time
            earliestTime[node] = min(earliestTime[node], earliestTime[neighbour]);
            // Articulation Point Condition (non-root)
            if (earliestTime[neighbour] >= discoveryTime[node] && parent != -1) {
                isAP[node] = true;
            }
            child++;
        }
        else { // back edge
            earliestTime[node] = min(earliestTime[node], discoveryTime[neighbour]);
        }
    }
    if (parent == -1 && child > 1) { // handle root node
        isAP[node] = true;
    }
}

int main() {
    int n = 5;
    int e = 5;
    vector<pair<int, int>> edges = { {0, 3}, {3, 4}, {0, 4}, {0, 1}, {1, 2} };
    // vector<pair<int, int>> edges = { {0, 1}, {1, 2}, {2, 0}, {1, 3}, {3, 4} };

    // adj list
    unordered_map<int, list<int>> adj;
    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i].first;
        int v = edges[i].second;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int timer = 0;
    vector<int> discoveryTime(n, -1);
    vector<int> earliestTime(n, -1);
    unordered_map<int, bool> isVisited;
    vector<bool> isAP(n, false);

    // dfs
    for (int i = 0; i < n; i++) {
        if (!isVisited[i]) {
            dfs(i, -1, discoveryTime, earliestTime, isVisited, adj, isAP, timer);
        }
    }

    // print ap
    cout << "articulation points are as follows: " << endl;
    for (int i = 0; i < n; i++) {
        if (isAP[i]) {
            cout << i << " ";
        }
    }cout << endl;
}

