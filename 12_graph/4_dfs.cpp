#include<iostream>
#include<unordered_map>
#include<list>
#include<set>
#include<vector>
#include<queue>
using namespace std;
/*
tc: using list O(v+e)
    using set  O((v+e)*log(v))
sc: O(v+e)
*/
void dfs(int node, unordered_map<int, bool>& visited, unordered_map<int, list<int>>& adj, vector<int>& component) {
    // storing the node
    component.push_back(node);
    visited[node] = true;

    //each connected node -> recursive call
    for (auto i : adj[node]) {
        if (!visited[i]) {
            dfs(i, visited, adj, component);
        }
    }
}

vector<vector<int>> depthFirstSearch(int V, int E, vector<vector<int>>& edges) {
    //prepare adjlist
    unordered_map<int, list<int>> adj;
    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i][0];
        int v = edges[i][1];

        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<vector<int>> ans;
    unordered_map<int, bool> visited;

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            vector<int> component;
            dfs(i, visited, adj, component);
            ans.push_back(component);
        }
    }
    return ans;
}





void dfs(int node, unordered_map<int, set<int>>& adjList, unordered_map<int, bool>& isVisited, vector<int>& component) {
    component.push_back(node);
    isVisited[node] = true;

    for (auto i : adjList[node]) {
        if (!isVisited[i]) {
            dfs(i, adjList, isVisited, component);
        }
    }
}
vector<vector<int>> DFS(int v, int e, vector<vector<int>>& edges) {
    // prepare adj list
    unordered_map<int, set<int>> adjList;
    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i][0];
        int v = edges[i][1];

        adjList[u].insert(v);
        adjList[v].insert(u);
    }

    vector<vector<int>> ans;
    unordered_map<int, bool> isVisited;

    for (int i = 0; i < v; i++) {
        if (!isVisited[i]) {
            vector<int> component;
            dfs(i, adjList, isVisited, component);
            ans.push_back(component);
        }
    }
    return ans;
}

int main() {
    vector<vector<int>> edges = { {0, 2}, {0,1}, {1,2}, {3, 4} };
    edges = DFS(5, 4, edges);
    for (auto i : edges) {
        for (auto j : i) {
            cout << j << " ";
        }cout << endl;
    }
}