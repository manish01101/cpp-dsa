#include<iostream>
#include<unordered_map>
#include<list>
#include<algorithm>
#include<set>
#include<stack>
#include<queue>
#include<vector>
using namespace std;


vector<int> shortestPath(vector<pair<int, int>>& edges, int n, int m, int s, int t) {
    // create adj list
    unordered_map<int, list<int>> adjList;
    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i].first;
        int v = edges[i].second;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    // bfs
    unordered_map<int, bool> isVisited;
    unordered_map<int, int> parent;
    queue<int> q;

    q.push(s);
    parent[s] = -1;
    isVisited[s] = true;
    while (!q.empty()) {
        int front = q.front();
        q.pop();
        for (auto neighbour : adjList[front]) {
            if (!isVisited[neighbour]) {
                isVisited[neighbour] = true;
                parent[neighbour] = front;
                q.push(neighbour);
            }
        }
    }
    // finding shortest path
    vector<int> ans;
    int currNode = t;
    ans.push_back(currNode);
    while (currNode != s) {
        currNode = parent[currNode];
        ans.push_back(currNode);
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

int main() {
    vector<pair<int, int>> edges = {{1, 2}, {1, 3}, {2, 4}, {3, 4}, {4, 5}};
    vector<int> ans = shortestPath(edges, 5, 5, 1, 5);
    for(int i: ans)cout << i << "->";
    cout << endl;
}