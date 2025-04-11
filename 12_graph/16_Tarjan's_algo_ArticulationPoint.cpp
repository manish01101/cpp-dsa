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
*/

int min(int a, int b) {
    if (a < b) return a;
    return b;
}

void dfs(int node, int parent, vector<int>& discoveryTime, vector<int>& earliestTime, unordered_map<int, bool>& isVisited, unordered_map<int, list<int>>& adj, vector<bool>& ap, int& timer) {

    isVisited[node] = true;
    discoveryTime[node] = earliestTime[node] = timer++;
    int child = 0;
    
    for (auto neighbour : adj[node]) {
        if (neighbour == parent) {
            continue;
        }
        if (!isVisited[neighbour]) {
            dfs(neighbour, node, discoveryTime, earliestTime, isVisited, adj, ap, timer);
            // update earliest time
            earliestTime[node] = min(earliestTime[node], earliestTime[neighbour]);
            // check AP or not
            if (earliestTime[neighbour] >= discoveryTime[node] && parent != -1) {
                ap[node] = true;
            }
            child++;
        }
        else {
            earliestTime[node] = min(earliestTime[node], discoveryTime[neighbour]);
        }
    }
    if (parent == -1 && child > 1) { // handle root node
        ap[node] = true;
    }
}

int main() {
    int n = 5;
    int e = 5;
    vector<pair<int, int>> edges;
    edges.push_back(make_pair(0, 3));
    edges.push_back(make_pair(3, 4));
    edges.push_back(make_pair(0, 4));
    edges.push_back(make_pair(0, 1));
    edges.push_back(make_pair(1, 2));

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
    vector<bool> ap(n, false);

    // dfs
    for (int i = 0; i < n; i++) {
        if (!isVisited[i]) {
            dfs(i, -1, discoveryTime, earliestTime, isVisited, adj, ap, timer);
        }
    }

    // print ap
    cout << "articulation points are as follows: " << endl;
    for (int i = 0; i < n; i++) {
        if (ap[i] != false) {
            cout << i << " ";
        }
    }cout << endl;
}