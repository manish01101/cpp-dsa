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
-> while visiting each neighbour, decrease thier indegree as thier parent is fetched, so now neighbour become parent
*/

// TC: O(V + E) , SC: O(V + E)
vector<int> topologicalSort(vector<vector<int>>& edges, int v, int e) {
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
        for (auto j : i.second) {
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
    return ans;
}