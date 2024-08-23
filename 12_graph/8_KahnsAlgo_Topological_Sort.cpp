#include<iostream>
#include<unordered_map>
#include<list>
#include<set>
#include<stack>
#include<queue>
#include<vector>
using namespace std;

/*
kahn algo uses bfs:
-> find indegree of all nodes
-> in queue, insert 0-indegree nodes
-> apply bfs
-> while visiting each neighbour, decrease their indegree as thier parent is fetched, so now neighbour will become parent and parent must have indegree 0

Kahn's algorithm is a classic method for performing a topological sort of a Directed Acyclic Graph (DAG). The algorithm works by repeatedly removing nodes with no incoming edges and updating the incoming edge counts of their neighboring nodes.
*/

// TC: O(V + E) , SC: O(V + E)
vector<int> kahnTopologicalSort(vector<vector<int>>& edges, int v, int e) {
    // creating adj list
    unordered_map<int, list<int>> adjList;
    for (int i = 0; i < e; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        adjList[u].push_back(v);
    }
    // finding all indegree
    vector<int> indegree(v, 0);
    for (auto i : adjList) {
        for (auto j : i.second) { // i.second = list of neighbour
            indegree[j]++;
        }
    }

    // 0 indegree -> push to q
    queue<int> q;
    for (int i = 0; i < v; i++) {
        if (indegree[i] == 0)
            q.push(i);
    }

    // do bfs
    vector<int> ans;
    while (!q.empty()) {
        int front = q.front();
        q.pop();

        // ans store
        ans.push_back(front);

        // neighbour indegree update
        for (auto neighbour : adjList[front]) {
            indegree[neighbour]--; // decrement indegree
            if (indegree[neighbour] == 0) {
                q.push(neighbour);
            }
        }
    }
    // If ans doesn't contain all vertices, there was a cycle
    if (ans.size() != v) {
        cout << "Graph has a cycle. Topological sort not possible.\n";
        return {};
    }

    return ans;
}