#include<iostream>
#include<unordered_map>
#include<list>
#include<vector>
#include<queue>
using namespace std;

/*
neglecting condition: visited as well as parent of curr node
cycle detection condition: visited and not parent of curr node
*/

bool isCyclicBFS(int node, unordered_map<int, list<int>>& adjList, unordered_map<int, bool>& isVisited) {

    unordered_map<int, int> parent;	// for storing parent node
    // handling first node of component
    parent[node] = -1;
    isVisited[node] = true;
    queue<int> q;
    q.push(node);

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        // extract all neighbour of that node
        for (auto neighbour : adjList[curr]) {
            if (!isVisited[neighbour]) {
                q.push(neighbour);
                isVisited[neighbour] = true;
                parent[neighbour] = curr;
            }
            else if (isVisited[neighbour] == true && neighbour != parent[curr]) {
                return true;
            }
        }
    }
    return false;
}

bool isCyclicDFS(int node, int parentNode, unordered_map<int, bool>& isVisited, unordered_map<int, list<int>>& adjList) {
    isVisited[node] = true;

    for (auto neighbour : adjList[node]) {
        if (!isVisited[neighbour]) {
            bool cycleDetected = isCyclicDFS(neighbour, node, isVisited, adjList);
            if (cycleDetected)
                return true;
        }
        else if (neighbour != parentNode) {
            // cycle present
            return true;
        }
    }
    return false;
}

// main function
string cycleDetection(vector<vector<int>>& edges, int n, int m) {
    //create adjacency list
    unordered_map<int, list<int>> adjList;
    for (int i = 0; i < m; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    unordered_map<int, bool> isVisited;

    // to handle disconnected components
    for (int i = 0; i < n; i++) {
        if (!isVisited[i]) {
            bool ans = isCyclicBFS(i, adjList, isVisited);
            // bool ans = isCyclicDFS(i, -1, visited, adj);
            if (ans == true)
                return "Yes";
        }
    }
    return "No";
}