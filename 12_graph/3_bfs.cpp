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
void prepareAdjList(unordered_map<int, list<int> >& adjList, vector<pair<int, int> >& edges) {
    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i].first;
        int v = edges[i].second;

        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
}

void bfs(unordered_map<int, list<int> >& adjList, unordered_map<int, bool>& visited, vector<int>& ans, int node) {
    queue<int> q;
    q.push(node);
    visited[node] = true;

    while (!q.empty()) {
        int frontNode = q.front();
        q.pop();

        //store frontNode into ans
        ans.push_back(frontNode);

        //traverse all neighbours of frontnode
        for (auto i : adjList[frontNode]) {
            if (!visited[i]) {
                q.push(i);
                visited[i] = true;
            }
        }
    }
}
// main fn
vector<int> BFS(int vertex, vector<pair<int, int> > edges) {
    unordered_map<int, list<int> > adjList;
    vector<int> ans;
    unordered_map<int, bool> visited;

    prepareAdjList(adjList, edges);

    // traverse all comp of a graph
    for (int i = 0; i < vertex; i++) {
        if (!visited[i]) {
            bfs(adjList, visited, ans, i);
        }
    }
    return ans;
}







void prepareAdjList(unordered_map<int, set<int>>& adjList, vector<vector<int>>& adj) {
    for (int i = 0; i < adj.size(); i++) {
        int u = adj[i][0];
        int v = adj[i][1];

        adjList[u].insert(v);
        adjList[v].insert(u);
    }
}
void bfs(unordered_map<int, set<int>>& adjList, vector<int>& ans, unordered_map<int, bool>& isVisited, int ele) {
    queue<int> q;
    q.push(ele);
    isVisited[ele] = true;

    while (!q.empty()) {
        int temp = q.front();
        q.pop();

        ans.push_back(temp);

        for (auto i : adjList[temp]) {
            if (!isVisited[i]) {
                q.push(i);
                isVisited[i] = true;
            }
        }
    }
}
vector<int> bfsTraversal(int n, vector<vector<int>>& adj) {
    unordered_map<int, set<int>> adjList;
    vector<int> ans;
    unordered_map<int, bool> isVisited;

    prepareAdjList(adjList, adj);

    for (int i = 0; i < n; i++) {
        if (!isVisited[i]) {
            bfs(adjList, ans, isVisited, i);
        }
    }
    return ans;
}

int main() {
    vector<vector<int>> adj = { {2}, {0, 1}, {0, 3}, {1,3} };
    vector<int> ans = bfsTraversal(4, adj);
    for (auto i : ans) {
        cout << i << " ";
    } cout << endl;
}