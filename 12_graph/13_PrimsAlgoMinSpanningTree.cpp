#include<iostream>
#include<unordered_map>
#include<list>
#include<set>
#include<vector>
#include<queue>
#include<limits.h>
using namespace std;
/*
What is Prim's Algorithm?
Prim's Algorithm is a greedy algorithm that finds a Minimum Spanning Tree (MST) for a weighted undirected graph. The MST is a subset of the edges that connects all the vertices together, without any cycles and with the minimum possible total edge weight.

Steps of Prim's Algorithm:

    Initialization: Start from any vertex and mark it as part of the MST.
    Edge selection: At each step, add the smallest-weight edge that connects a vertex in the MST to a vertex outside the MST.
    Repeat: Repeat step 2 until all vertices are included in the MST.

PseudoCode:
1. Initialize a min-heap or priority queue.
2. Mark all vertices as not included in MST.
3. Set the key value of the start vertex to 0 and all others to infinity.
4. While MST does not contain all vertices:
   a. Pick the vertex u with the minimum key value not in MST.
   b. Include u in MST.
   c. For every adjacent vertex v of u, if v is not in MST and weight(u, v) is less than key[v], update key[v] as weight(u, v).

if graph converted into tree, it has n nodes and n-1 edges and every node is reacheable by every other node
*/

// main fn
vector<pair<pair<int, int>, int>> calculatePrimsMST(int V, vector<pair<pair<int, int>, int>>& g) {
    // create adj list
    unordered_map<int, list<pair<int, int>>> adj;
    for (int i = 0; i < g.size(); i++) {
        int u = g[i].first.first;
        int v = g[i].first.second;
        int w = g[i].second;
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }
    // make needed three data structure
    vector<int> weight(V + 1, INT_MAX); // n+1=>for fetching node with index 1-based indexing
    vector<bool> isNodeInMstVisited(V + 1, false);
    vector<int> parent(V + 1, -1);

    // starting the algo 
    int src = 1;
    weight[src] = 0;
    parent[src] = -1;

    for (int i = 1; i < V; i++) {
        // STEP 1: find node with min weight
        int miniWeight = INT_MAX;
        int node;
        for (int v = 1; v <= V; v++) {
            if (isNodeInMstVisited[v] == false && weight[v] < miniWeight) {
                node = v;
                miniWeight = weight[v];
            }
        }
        if (isNodeInMstVisited[node])
            continue;
        // STEP 2: mark visited of min node as true;
        isNodeInMstVisited[node] = true;
        // STEP 3: check its adjacent nodes
        for (auto it : adj[node]) {
            int neighbourNode = it.first;
            int neighbourWeight = it.second;
            if (isNodeInMstVisited[neighbourNode] == false && neighbourWeight < weight[neighbourNode]) {
                weight[neighbourNode] = neighbourWeight;
                parent[neighbourNode] = node;
            }
        }
    }
    // ans -> mini spanning tree
    vector<pair<pair<int, int>, int>> result;
    for (int i = 2; i <= V; i++) {
        result.push_back({ {parent[i], i}, weight[i] });
    }
    return result;
}





/* USING MIN HEAP */
vector<pair<pair<int, int>, int>> calculatePrimsMST2(int V, vector<pair<pair<int, int>, int>>& g) {
    // create adj list
    unordered_map<int, list<pair<int, int>>> adj;
    for (int i = 0; i < g.size(); i++) {
        int u = g[i].first.first;
        int v = g[i].first.second;
        int w = g[i].second;
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }
    // make needed three data structure
    vector<int> weight(V + 1, INT_MAX); // n+1 for 1 based indexing
    vector<bool> isNodeInMstVisited(V + 1, false);
    vector<int> parent(V + 1, -1);
    // pair<weight, node>
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;

    // starting the algo 
    int src = 1;
    weight[src] = 0;
    parent[src] = -1;

    pq.push({ weight[src], src });

    while (!pq.empty()) {
        // STEP 1: find node with min weight
        int node = pq.top().second;
        int nodeWeight = pq.top().first;
        pq.pop();

        if (isNodeInMstVisited[node])
            continue;
        // STEP 2: mark min weight node as visited
        isNodeInMstVisited[node] = true;

        // STEP 3: go for adjacent node
        for (auto& it : adj[node]) {
            int neighbourNode = it.first;
            int neighbourWeight = it.second;

            if (isNodeInMstVisited[neighbourNode] == false && neighbourWeight < weight[neighbourNode]) {
                weight[neighbourNode] = neighbourWeight;
                parent[neighbourNode] = node;
                pq.push({ weight[neighbourNode], neighbourNode });
            }
        }
    }

    // ans -> mini spanning tree
    vector<pair<pair<int, int>, int>> result;
    for (int i = 2; i <= V; i++) {
        result.push_back({ {parent[i], i}, weight[i] });
    }
    return result;
}

int printCountMst(vector<pair<pair<int, int>, int>>& mst) {
    int wt = 0;
    cout << "Edges \tWeight\n";
    for (auto& item : mst) {
        wt += item.second;
        cout << item.first.first << '-' << item.first.second << "\t" << item.second << "\n";
    }
    return wt;
}

int main() {
    int n = 5;
    vector<pair<pair<int, int>, int>> edges = {
        {{1,2},2}, {{1,4},6}, {{2,3},3}, {{2,4},8}, {{2,5},5},
        {{3,5},7}, {{4,5},9}
    };
    auto mst = calculatePrimsMST(n, edges);
    int totalWeight = printCountMst(mst);
    cout << "min wt is: " << totalWeight << endl;
}