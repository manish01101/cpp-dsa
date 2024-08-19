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
*/

// TC: O(E log V)
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

    // process, initialize distance and set with source node
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


vector <int> dijkstra(int V, vector<vector<int>> adj[], int S) {
    // dist array and set for stoting (dist[node), node
    vector<int> dist(V, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // processing
    dist[S] = 0;
    pq.push(make_pair(dist[S], S));

    while (!pq.empty()) {
        auto temp = pq.top();
        pq.pop();

        int tempNode = temp.second;
        int tempWeight = temp.first;

        for (auto neighbour : adj[tempNode]) {
            int neighbourNode = neighbour[0];
            int neighbourWeight = neighbour[1];

            if (tempWeight + neighbourWeight < dist[neighbourNode]) {
                // first delete the old record for that node
                // auto oldRecord = st.find(make_pair(dist[neighbour[0]], neighbour[0]));
                // if (oldRecord != st.end()) {
                //     st.erase(oldRecord);
                // }

                // update distance
                dist[neighbourNode] = tempWeight + neighbourWeight;

                pq.push({ dist[neighbourNode], neighbourNode });
            }

        }
    }
    return dist;
}