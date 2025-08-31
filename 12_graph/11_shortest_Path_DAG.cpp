/*

| Feature                   | **Topological Sort + DP**  | **Dijkstra**                     | **Bellman-Ford**         | **Floyd-Warshall**       |
| ------------------------- | -------------------------- | -------------------------------- | ------------------------ |------------------------ |
| Graph Requirement         | **Directed Acyclic Graph** | Any graph (no negative weights)  | Any graph                |Any                      |
| Supports Negative Weights | ✅ Yes                      | ❌ No                             | ✅ Yes                  |✅ Yes                    |
| Detects Negative Cycles   | ❌ No                       | ❌ No                             | ✅ Yes                  |✅ Yes                    |
| Edge Relaxation           | Once per edge              | Multiple (via priority queue)    | Up to V–1 times per edge |
| Time Complexity           | `O(V + E)`                 | `O((V + E) log V)` with min-heap | `O(V × E)`               |`O(V³)`                  |
| Space Complexity          | `O(V + E)`                 | `O(V + E)`                       | `O(V+E)`                   |O(V²)                  |
| Mutability of Graph       | Must be a DAG              | Must not have negative edges     | Can be any               |
| **Use Case**                | Fast on DAGs              | Fast on positive weights        | Any graph, cycle check   | All-pairs shortest paths |
| **Shortest Path Type**      | Single Source             | Single Source                   | Single Source            | All Pairs                |

*/
#include <iostream>
#include <unordered_map>
#include <list>
#include <stack>
#include <vector>
#include <limits.h>
using namespace std;

class Graph {
private:
    unordered_map<int, list<pair<int, int>>> adjList;

    void dfsHelper(int node, unordered_map<int, bool>& isVisited, stack<int>& topoStack) {
        isVisited[node] = true;
        for (auto& neighbor : adjList[node]) {
            if (!isVisited[neighbor.first]) {
                dfsHelper(neighbor.first, isVisited, topoStack);
            }
        }
        topoStack.push(node);
    }

public:
    void addEdge(int u, int v, int weight) {
        adjList[u].emplace_back(v, weight);
    }

    void printAdjList() const {
        cout << "Adjacency List:\n";
        for (const auto& [u, neighbors] : adjList) {
            cout << u << " -> ";
            for (const auto& [v, wt] : neighbors) {
                cout << "(" << v << "," << wt << ") ";
            }
            cout << "\n";
        }
    }

    vector<int> shortestPathDAG(int src, int totalNodes) {
        unordered_map<int, bool> isVisited;
        stack<int> topoStack;

        // Perform topological sort
        for (int i = 0; i < totalNodes; ++i) {
            if (!isVisited[i]) {
                dfsHelper(i, isVisited, topoStack);
            }
        }

        // Initialize distances
        vector<int> dist(totalNodes, INT_MAX);
        dist[src] = 0;

        // Relax edges according to topological order
        while (!topoStack.empty()) {
            int u = topoStack.top();
            topoStack.pop();

            if (dist[u] != INT_MAX) {
                for (auto& [v, weight] : adjList[u]) {
                    if (dist[u] + weight < dist[v]) {
                        dist[v] = dist[u] + weight;
                    }
                }
            }
        }

        return dist;
    }
};

int main() {
    Graph g;
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 3, 6);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 4, 4);
    g.addEdge(2, 5, 2);
    g.addEdge(3, 4, -1);
    g.addEdge(4, 5, -2);

    g.printAdjList();

    int src = 0;
    int totalNodes = 6;

    vector<int> shortestDistances = g.shortestPathDAG(src, totalNodes);

    cout << "\nShortest distances from node " << src << ":\n";
    for (int i = 0; i < totalNodes; ++i) {
        if (shortestDistances[i] == INT_MAX)
            cout << "INF ";
        else
            cout << shortestDistances[i] << " ";
    }
    cout << endl;

    return 0;
}
