#include<iostream>
#include<unordered_map>
#include<list>
#include<set>
#include<queue>
#include<vector>
using namespace std;

bool checkCycleDFS(int node, unordered_map<int, bool> &visited, unordered_map<int, bool> &dfsVisited, unordered_map<int, list<int>> &adj) {
  visited[node] = true;
  dfsVisited[node] = true;

  for(auto neighbour: adj[node]) {
    if(!visited[neighbour]) {
      bool cycleDetected = checkCycleDFS(neighbour, visited, dfsVisited, adj);
      if(cycleDetected) return true;
    }
    else if (dfsVisited[neighbour]) {
      return true;
    }
  }
  dfsVisited[node] = false;
  return false;
}

// main fn
int detectCycleInDirectedGraph(int n, vector<pair<int, int>> &edges) {
  //creating adj list
  unordered_map<int, list<int>> adj;
  for(int i=0; i<edges.size(); i++) {
    int u = edges[i].first;
    int v = edges[i].second;
    // for directed graph
    adj[u].push_back(v);
  }

  unordered_map<int, bool> visited;
  unordered_map<int, bool> dfsVisited;
  // call dfs for all components
  for(int i=1; i<=n; i++) {
    if(!visited[i]) {
      bool cycleFound = checkCycleDFS(i, visited, dfsVisited, adj);
      if(cycleFound) return true;
    }
  }
  return false;
}