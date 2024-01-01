#include<iostream>
#include<unordered_map>
#include<list>
#include<vector>
#include<queue>
using namespace std;

bool isCyclicBFS(int node, unordered_map<int, bool> &visited, unordered_map<int, list<int>> &adj) {
  // data str. for storing parent node
  unordered_map<int, int> parent;
  // handling first node of component
  parent[node] = -1;
  visited[node] = 1;
  queue<int> q;
  q.push(node);

  while (!q.empty()) {
    int front = q.front();
    q.pop();

    // extract all neighbour of that node
    for(auto neighbour : adj[front]) {
      if(visited[neighbour] == true && neighbour != parent[front]) {
        return true;
      }
      else if (!visited[neighbour]) {
        q.push(neighbour);
        visited[neighbour] = 1;
        parent[neighbour] = front;
      }
    }
  }
  return false;
}

bool isCyclicDFS(int node, int parentNode, unordered_map<int, bool> &visited, unordered_map<int, list<int>> &adj) {
  visited[node] = true;

  for(auto neighbour : adj[node]) {
    if(!visited[neighbour]) {
      bool cycleDetected = isCyclicDFS(neighbour, node, visited, adj);
      if(cycleDetected) return true;
    }
    else if(neighbour != parentNode) {
      // cycle present
      return true;
    }
  }
  return false;
}

// main function
string cycleDetection (vector<vector<int>> &edges, int n, int m) { //n-vertices, m-edges
  //create adjacency list
  unordered_map<int, list<int>> adj;
  for(int i=0; i<m; i++) {
    int u = edges[i][0];
    int v = edges[i][1];
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  unordered_map<int, bool> visited;

  // to handle disconnected components
  for(int i=0; i<n; i++) {
    if(!visited[i]) {
      bool ans = isCyclicBFS(i, visited, adj);
      // bool ans = isCyclicDFS(i, -1, visited, adj);
      if(ans == 1) return "Yes";
    }
  }
  return "No";
}