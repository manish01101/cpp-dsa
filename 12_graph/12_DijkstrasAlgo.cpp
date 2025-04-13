#include<iostream>
#include<unordered_map>
#include<queue>
#include<list>
#include<set>
#include<vector>
#include<limits.h>
using namespace std;

/*
dijkstra algo not work on -ve weight
used to find the shortest paths from a source node to all other nodes in a weighted graph. It is particularly efficient for graphs with non-negative edge weights.
*/

/* USING SET => TC: O((V+E)logV),  sc: O(V+E) */
vector<int> Dijkstra(vector<vector<int>>& vec, int vertices, int edges, int source) {
    // create adj list
    unordered_map<int, list<pair<int, int>>> adjList;
    for (int i = 0; i < edges; i++) {
        int u = vec[i][0];
        int v = vec[i][1];
        int weight = vec[i][2];
        adjList[u].push_back(make_pair(v, weight));
        adjList[v].push_back(make_pair(u, weight));
    }

    // dist array
    vector<int> dist(vertices, INT_MAX);
    // set for storing <min_dist,  node_val>
    set<pair<int, int>> st;

    // process: initialize distance and set with source node
    dist[source] = 0;
    st.insert(make_pair(dist[source], source));

    while (!st.empty()) {
        auto temp = *(st.begin());
        st.erase(st.begin());

        // neighbour traverse
        for (auto neighbour : adjList[temp.second]) {
            if (temp.first + neighbour.second < dist[neighbour.first]) {
                // delete record with dist[neighbour.first], neighbour.first
                auto record = st.find(make_pair(dist[neighbour.first], neighbour.first));
                // if found erase it
                if (record != st.end()) {
                    st.erase(record);
                }

                // update distance
                dist[neighbour.first] = temp.first + neighbour.second;
                // push updated record in set
                st.insert(make_pair(dist[neighbour.first], neighbour.first));
            }
        }
    }
    return dist;
}

/* USING MIN HEAP => Time Complexity: O((V+E)logV) Space Complexity: O(V+E)*/
vector<int> dijkstra(int V, vector<vector<pair<int, int>>> &adj, int S) {
    vector<int> dist(V, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;

    // Initializing source
    dist[S] = 0;
    minHeap.push({0, S});

    while (!minHeap.empty()) {
        auto [tempWeight, tempNode] = minHeap.top(); // Structured binding
        minHeap.pop();

        // Optimization: Skip outdated distances
        if (dist[tempNode] < tempWeight) continue;

        for (auto& neighbour : adj[tempNode]) {
            int neighbourNode = neighbour.first;
            int neighbourWeight = neighbour.second;

            if (tempWeight + neighbourWeight < dist[neighbourNode]) {
                dist[neighbourNode] = tempWeight + neighbourWeight;
                minHeap.push({dist[neighbourNode], neighbourNode});
            }
        }
    }
    return dist;
}