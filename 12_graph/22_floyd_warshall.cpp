#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int INF = INT_MAX;

// Function to print the distance matrix
void printDistanceMatrix(const vector<vector<int>>& dist) {
    int V = dist.size();
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (dist[i][j] == INF)
                cout << "INF\t";
            else
                cout << dist[i][j] << "\t";
        }
        cout << endl;
    }
}

// Floyd-Warshall Algorithm
void floydWarshall(vector<vector<int>>& graph) {
    int V = graph.size();
    vector<vector<int>> dist = graph;

    for (int k = 0; k < V; ++k) { // Intermediate node
        for (int i = 0; i < V; ++i) { // Start node
            for (int j = 0; j < V; ++j) { // End node
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    cout << "All-pairs shortest path matrix:\n";
    printDistanceMatrix(dist);
}

// Example usage
int main() {
    int V = 4;
    vector<vector<int>> graph = {
        {0,   5,   4, 10},
        {INF, 0,   3,   INF},
        {INF, INF, 0,   1},
        {INF, INF, INF, 0}
    };

    floydWarshall(graph);

    return 0;
}
