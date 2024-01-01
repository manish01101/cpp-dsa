#include<iostream>
#include<unordered_map>
#include<list>
#include<set>
#include<stack>
#include<queue>
#include<vector>
using namespace std;

void topoSort(int node, unordered_map<int, bool> &visited, stack<int> &s, unordered_map<int, list<int>> &adj) {
  visited[node] = 1;

  for(auto neighbour : adj[node]) {
    if(!visited[neighbour]) {
      topoSort(neighbour, visited, s, adj);
    }
  }
  // at returning time push node to stack
  s.push(node);
}

// main fn
vector<int> topologicalSort(vector<vector<int>> &edges, int v, int e) {
  // creating adj list
  unordered_map<int, list<int>> adj;
  for(int i=0; i<edges.size(); i++) {
    int u = edges[i][0];
    int v = edges[i][1];
    adj[u].push_back(v);
  }

  unordered_map<int, bool> visited;
  stack<int> s;
  // call dfs topological sort util fn for all component
  for(int i=0; i<v; i++) {
    if(!visited[i]) {
      topoSort(i, visited, s, adj);
    }
  }

  // storing answer
  vector<int> ans;
  while (!s.empty()) {
    ans.push_back(s.top());
    s.pop();
  }
  return ans;
}