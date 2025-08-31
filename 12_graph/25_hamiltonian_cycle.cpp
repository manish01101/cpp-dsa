#include <iostream>
#include <vector>

using namespace std;
/*

A Hamiltonian Cycle is a cycle in a graph that:
    Visits every vertex exactly once
    Returns to the starting vertex

Approach (Backtracking)
    Start from a vertex (commonly vertex 0).
    Try to add vertices one by one to the current path.
    Before adding, check if the vertex is:
        Adjacent to the last vertex in the path
        Not already included in the path
    If all vertices are added and there’s an edge from the last vertex to the first, it forms a Hamiltonian cycle.
    If adding a vertex leads to a dead end, backtrack and try a different vertex.

*/
class HamiltonianCycle {
private:
    int V;
    vector<vector<int>> graph;
    vector<int> path;

    bool isSafe(int v, int pos) {
        // Check if current vertex is adjacent to the previous vertex in path
        if (graph[path[pos - 1]][v] == 0)
            return false;

        // Check if vertex has already been included
        for (int i = 0; i < pos; i++)
            if (path[i] == v)
                return false;

        return true;
    }

    bool hamiltonianUtil(int pos) {
        if (pos == V) {
            // If there's an edge from last vertex to first, cycle exists
            return graph[path[pos - 1]][path[0]] == 1;
        }

        for (int v = 1; v < V; v++) {
            if (isSafe(v, pos)) {
                path[pos] = v;
                if (hamiltonianUtil(pos + 1))
                    return true;

                // Backtrack
                path[pos] = -1;
            }
        }

        return false;
    }

public:
    HamiltonianCycle(const vector<vector<int>>& g) : graph(g), V(g.size()) {
        path = vector<int>(V, -1);
    }

    void findCycle() {
        path[0] = 0;

        if (!hamiltonianUtil(1)) {
            cout << "No Hamiltonian Cycle found.\n";
            return;
        }

        cout << "Hamiltonian Cycle: ";
        for (int v : path)
            cout << v << " ";
        cout << path[0] << "\n"; // to complete the cycle
    }
};

int main() {
    // Example graph (Undirected and fully connected for cycle)
    vector<vector<int>> graph = {
        {0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0}
    };

    HamiltonianCycle hc(graph);
    hc.findCycle();

    return 0;
}
