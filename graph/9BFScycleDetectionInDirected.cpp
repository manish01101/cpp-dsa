#include<iostream>
#include<unordered_map>
#include<list>
#include<set>
#include<stack>
#include<queue>
#include<vector>
using namespace std;

// bfs cycle detection in directed graph
// using kahn's algo

int detectCycleInDirectedGraph (int n, vector<pair<int, int>> &edges) {
  // creating adj list
  unordered_map<int, list<int>> adj;
  for(int i=0; i<edges.size(); i++) {
    int u = edges[i].first - 1;
    int v = edges[i].second - 1;
    adj[u].push_back(v);
  }
  // finding all indegree
  vector<int> indegree(n);
  for(auto i : adj) {
    for(auto j : i.second) {
      indegree[j]++;
    }
  }

  // 0 indegree -> push to q
  queue<int> q;
  for(int i=0; i<n; i++) {
    if(indegree[i] == 0)
      q.push(i);
  }

  // do bfs
  int cnt = 0;
  while(!q.empty()) {
    int front = q.front();
    q.pop();

    // increment count
    cnt++;

    // neighbour indegree update
    for(auto neighbour : adj[front]) {
      indegree[neighbour]--;
      if(indegree[neighbour] == 0)
        q.push(neighbour);
    }
  }  
  if(cnt == n) return false;
  else return true;
}