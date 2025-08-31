#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

/*
A greedy + DFS/BFS based method to compute the maximum flow in a flow network.
Use Case:
    Network routing
    Bipartite matching
    Circulation problems
    Job scheduling
    Image segmentation (computer vision)
Core Idea:
    Repeatedly find augmenting paths with available capacity.
    Update residual capacities.
    Total flow is the sum of bottlenecks on these paths.

complexity: O(E·maxFlow)


1. DFS-based Ford-Fulkerson (Greedy Augmenting Paths)
✅ Characteristics:
    Search method: Depth-First Search (DFS)
    Path selection: Greedily picks any augmenting path it finds
    Order of traversal: May find long paths or inefficient ones
    Speed: Fast on small graphs, but can be very slow or even infinite loop on graphs with cycles and irrational capacities
❌ Drawbacks:
    Can fall into infinite loops if capacities are irrational
    Poor path choices can lead to many unnecessary iterations
    Not guaranteed to run in polynomial time

2. BFS-based Ford-Fulkerson (Edmonds-Karp Algorithm)
✅ Characteristics:
    Search method: Breadth-First Search (BFS)
    Path selection: Always chooses the shortest augmenting path (fewest edges)
    Order of traversal: More structured and efficient
    Time complexity: O(V × E²) — polynomial time
✅ Benefits:
    Guaranteed to terminate
    Runs efficiently even on moderately large graphs
    Recommended standard approach in practice

| Feature                    | DFS-based Ford-Fulkerson       | BFS-based Ford-Fulkerson (Edmonds-Karp) |
| -------------------------- | ------------------------------ | --------------------------------------- |
| **Search method**          | DFS                            | BFS                                     |
| **Augmenting path choice** | Any path (greedy)              | Shortest path (in edges)                |
| **Time Complexity**        | `O(E × max_flow)` (can be bad) | `O(V × E²)` (polynomial)                |
| **Termination guarantee**  | ❌ Not always                   | ✅ Always                                |
| **Practical use**          | Small graphs only              | Real-world max flow problems            |

*/
const int INF = 1e9;
const int MAXN = 100;

int capacity[MAXN][MAXN]; // capacity[u][v] = capacity of edge u->v
bool visited[MAXN];
int n, source, sink;

// DFS to find an augmenting path and return its flow
int dfs(int u, int flow) {
    if (u == sink) return flow;
    visited[u] = true;

    for (int v = 0; v < n; ++v) {
        if (!visited[v] && capacity[u][v] > 0) {
            int bottleneck = dfs(v, min(flow, capacity[u][v]));
            if (bottleneck > 0) {
                capacity[u][v] -= bottleneck;
                capacity[v][u] += bottleneck;
                return bottleneck;
            }
        }
    }
    return 0;
}

int fordFulkerson() {
    int max_flow = 0, flow;
    while (true) {
        memset(visited, false, sizeof(visited));
        flow = dfs(source, INF);
        if (flow == 0) break; // No more augmenting path
        max_flow += flow;
    }
    return max_flow;
}

int main() {
    n = 6; // number of nodes
    source = 0;
    sink = 5;

    // Example: capacity[u][v] = capacity of edge u -> v
    capacity[0][1] = 16;
    capacity[0][2] = 13;
    capacity[1][2] = 10;
    capacity[1][3] = 12;
    capacity[2][1] = 4;
    capacity[2][4] = 14;
    capacity[3][2] = 9;
    capacity[3][5] = 20;
    capacity[4][3] = 7;
    capacity[4][5] = 4;

    cout << "Maximum Flow: " << fordFulkerson() << endl;
    return 0;
}


#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

bool bfs(vector<vector<int>>& rGraph, int s, int t, vector<int>& parent) {
    int V = rGraph.size();
    vector<bool> visited(V, false);
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v = 0; v < V; ++v) {
            if (!visited[v] && rGraph[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return visited[t];
}

int fordFulkerson(vector<vector<int>>& graph, int s, int t) {
    int V = graph.size();
    vector<vector<int>> rGraph = graph;
    vector<int> parent(V);
    int maxFlow = 0;

    while (bfs(rGraph, s, t, parent)) {
        int pathFlow = INT_MAX;
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, rGraph[u][v]);
        }
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            rGraph[u][v] -= pathFlow;
            rGraph[v][u] += pathFlow;
        }
        maxFlow += pathFlow;
    }

    return maxFlow;
}

int main() {
    vector<vector<int>> graph = {
        {0, 10, 5, 0, 0, 0},
        {0, 0, 15, 10, 0, 0},
        {0, 0, 0, 0, 10, 0},
        {0, 0, 0, 0, 0, 10},
        {0, 0, 0, 10, 0, 10},
        {0, 0, 0, 0, 0, 0}
    };
    int s = 0, t = 5;
    cout << "Ford-Fulkerson (Max Flow): " << fordFulkerson(graph, s, t) << endl;
    return 0;
}
