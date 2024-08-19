#include<iostream>
#include<unordered_map>
#include<list>
#include<set>
#include<queue>
#include<vector>
using namespace std;

/*
make two mapping
isVisited & isDfsCall
for every call of ele, make isDfsCall true and while returning make false
-> if isVisited[node]= true && isDfsCall[node] == true , cycle present
*/


bool checkCycleWithDFS(int node, unordered_map<int, list<int>>& adjList, unordered_map<int, bool>& isVisited, unordered_map<int, bool>& isDFSCalled) {
    isVisited[node] = true;
    isDFSCalled[node] = true;

    for (auto neighbour : adjList[node]) {
        if (!isVisited[neighbour]) {
            bool cycleFound = checkCycleWithDFS(neighbour, adjList, isVisited, isDFSCalled);
            if (cycleFound) {
                return true;
            }
        }
        else if (isDFSCalled[neighbour]) { // here isVisited[neighbour] == ture
            return true;
        }
    }
    isDFSCalled[node] = false;
    return false;
}
int detectCycleInDirectedGraph(int n, vector<pair<int, int>>& edges) {
    // creating adj list
    unordered_map<int, list<int>> adjList;
    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i].first;
        int v = edges[i].second;
        adjList[u].push_back(v);
    }

    unordered_map<int, bool> isVisited;
    unordered_map<int, bool> isDFSCalled;
    for (int i = 1; i <= n; i++) {
        if (!isVisited[i]) {
            bool cycleFound = checkCycleWithDFS(i, adjList, isVisited, isDFSCalled);
            if (cycleFound) {
                return true;
            }
        }
    }
    return false;
}