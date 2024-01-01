#include<iostream>
#include<unordered_map>
#include<list>
#include<set>
#include<vector>
#include<limits.h>
using namespace std;


// main fn
vector<pair<pair<int,int>, int>> calculatePrimsMST(int n, int m, vector<pair<pair<int, int>, int>> &g) {
  // create adj list
  unordered_map<int, list<pair<int,int>>> adj;
  for(int i=0; i<g.size(); i++) {
    int u = g[i].first.first;
    int v = g[i].first.second;
    int w = g[i].second;
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
  }
  // make needed three data structure
  // n+1=>for fetching node with index
  vector<int> key(n+1);
  vector<bool> mst(n+1);
  vector<int> parent(n+1);
  
  // initialize all ds with initial val
  for(int i=0; i<=n; i++) {
    key[i] = INT_MAX;
    mst[i] = false;
    parent[i] = -1;
  }

  // starting the algo
  key[1] = 0;
  parent[1] = -1;

  for(int i=1; i<n; i++) {

    int mini = INT_MAX;
    int u;
    // find node with min val
    // this can be optimised by min heap
    for(int v=1; v<=n; v++) {
      if(mst[v] == false && key[v] < mini) {
        u = v;
        mini = key[v];
      }
    }

    // mark min node as true;
    mst[u] = true;

    // check its adjacent nodes
    // this can be optimised by min heap
    for(auto it: adj[u]) {
      int v = it.first;
      int w = it.second;
      if(mst[v] == false && w < key[v]) {
        parent[v] = u;
        key[v] = w;
      }
    }
  }

  // ans
  vector<pair<pair<int,int>, int>> result;
  for(int i=2; i<=n; i++) {
    result.push_back(make_pair(make_pair(parent[i], i), key[i]));
    // or
    // result.push_back({{parent[i], i}, key[i]});
  }
  return result;
}