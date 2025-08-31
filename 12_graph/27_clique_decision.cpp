#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class Graph {
private:
    int V;
    vector<vector<bool>> adj;

public:
    Graph(int V) : V(V), adj(V, vector<bool>(V, false)) { }

    void addEdge(int u, int v) {
        adj[u][v] = true;
        adj[v][u] = true; // Undirected graph
    }

    bool isClique(const vector<int>& subset) {
        for (int i = 0; i < subset.size(); i++) {
            for (int j = i + 1; j < subset.size(); j++) {
                if (!adj[subset[i]][subset[j]]) return false;
            }
        }
        return true;
    }

    bool hasCliqueOfSize(int k) {
        vector<int> vertices(V);
        for (int i = 0; i < V; i++) vertices[i] = i;

        vector<int> subset(k);

        // Generate all combinations of size k
        return generateCombinations(vertices, subset, 0, 0, k);
    }

private:
    bool generateCombinations(const vector<int>& vertices, vector<int>& subset, int start, int depth, int k) {
        if (depth == k) {
            return isClique(subset);
        }
        for (int i = start; i <= vertices.size() - (k - depth); i++) {
            subset[depth] = vertices[i];
            if (generateCombinations(vertices, subset, i + 1, depth + 1, k)) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    int V = 5;
    Graph g(V);

    // Create edges
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    int k = 3;
    if (g.hasCliqueOfSize(k))
        cout << "Graph contains a clique of size " << k << endl;
    else
        cout << "No clique of size " << k << " found." << endl;

    return 0;
}
