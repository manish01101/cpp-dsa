#include<iostream>
#include<unordered_map>
#include<list>
#include<set>
#include<stack>
#include<queue>
#include<vector>
using namespace std;

/*
DAG-> directed acyclic graph
topological sort only work on DAG
topological sort-> linear ordering of vertices such that for every edge u-v, u always before v in that orderin
*/


void topoSort(int node, unordered_map<int, list<int>>& adjList, unordered_map<int, bool>& isVisited, stack<int>& s) {
    isVisited[node] = true;
    for (auto neighbour : adjList[node]) {
        if (!isVisited[neighbour]) {
            topoSort(neighbour, adjList, isVisited, s);
        }
    }
    s.push(node);
}
vector<int> topologicalSort(vector<vector<int>>& edges, int v, int e) {
    // creating adj list
    unordered_map<int, list<int>> adjList;
    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        adjList[u].push_back(v);
    }

    unordered_map<int, bool> isVisted;
    stack<int> s;
    // dfs call for topological solr
    for (int node = 0; node < v; node++) {
        if (!isVisted[node]) {
            topoSort(node, adjList, isVisted, s);
        }
    }

    // storing ans in vector
    vector<int> ans;
    while (!s.empty()) {
        ans.push_back(s.top());
        s.pop();
    }
    return ans;
}
