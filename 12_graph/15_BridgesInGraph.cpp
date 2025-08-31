#include<iostream>
#include<unordered_map>
#include<list>
#include<set>
#include<algorithm>
#include<vector>
#include<limits.h>
using namespace std;

/*
bridge -> that edge, which increases the no. of components after removing it.

| Feature             | Articulation Point                       | Bridge                                   |
| ------------------- | ---------------------------------------- | ---------------------------------------- |
| What is removed?    | **Node** (and all its edges)             | **Edge** only                            |
| Result of removal   | Graph may split into multiple components | Graph may split into multiple components |
| Applies to          | **Vertex**                               | **Edge**                                 |
| Example             | Node `1` in triangle graph with a tail   | Edge `(1,2)` in a linear path            |
| Detection algorithm | Tarjan's Algorithm                       | Also uses Tarjan's Algorithm (variant)   |
| Use case            | Network weak points (like routers)       | Communication links, roads, cables       |

*/

void dfs(int node, int parent, int& timer, vector<int>& discoveryTime, vector<int>& earliestTime, vector<vector<int>>& bridges, unordered_map<int, list<int>>& adj, unordered_map<int, bool>& isVisited) {

    isVisited[node] = true;
    discoveryTime[node] = earliestTime[node] = timer++;

    for (auto neighbour : adj[node]) {
        if (neighbour == parent)
            continue;
        if (!isVisited[neighbour]) {
            dfs(neighbour, node, timer, discoveryTime, earliestTime, bridges, adj, isVisited);

            earliestTime[node] = min(earliestTime[node], earliestTime[neighbour]);
            // check edge is bridge
            if (earliestTime[neighbour] > discoveryTime[node]) {
                bridges.push_back({node, neighbour});
            }
        }
        else {
            // node already visited and not parent
            // back edge
            earliestTime[node] = min(earliestTime[node], discoveryTime[neighbour]);
        }
    }
}


// main fn
vector<vector<int>> findBridges(vector<vector<int>>& edges, int v, int e) {
    // adj list
    unordered_map<int, list<int>> adj;
    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int timer = 0;
    vector<int> discoveryTime(v, -1); // track node visited when
    vector<int> earliestTime(v, -1); // earliest possible time to reach node
    int parent = -1; // to track parent
    unordered_map<int, bool> isVisited;

    vector<vector<int>> bridges;
    // dfs
    for (int i = 0; i < v; i++) {
        if (!isVisited[i]) {
            dfs(i, parent, timer, discoveryTime, earliestTime, bridges, adj, isVisited);
        }
    }
    return bridges;
}

int main() {
    int v = 5; 
    int e = 5; 

    vector<vector<int>> edges = {
        {0, 1},
        {1, 2},
        {2, 0},
        {1, 3},
        {3, 4}
    };

    vector<vector<int>> bridges = findBridges(edges, v, e);

    cout << "Bridges in the graph:\n";
    for (auto& bridge : bridges) {
        cout << bridge[0] << " - " << bridge[1] << "\n";
    }

    return 0;
}
