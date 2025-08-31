
/*
The Traveling Salesman Problem (TSP) asks:
"Given a list of cities and distances between them, what is the shortest possible route that visits each city exactly once and returns to the origin city?"

TSP Algorithm (Backtracking or Brute Force) – Steps in Short:
        Start from a source city (commonly city 0).
        Try all permutations of the remaining cities.
        Calculate the total tour cost for each permutation (including return to start).
        Track the minimum cost tour.
        Return the best (shortest) tour and its cost.
Time Complexity: O(n!) — only suitable for small n (≤10–12).
*/

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class TSP {
private:
    int V;
    vector<vector<int>> graph;
    vector<bool> visited;
    int minCost;

    void tspUtil(int pos, int count, int cost, int start) {
        if (count == V && graph[pos][start]) {
            minCost = min(minCost, cost + graph[pos][start]);
            return;
        }

        for (int i = 0; i < V; i++) {
            if (!visited[i] && graph[pos][i]) {
                visited[i] = true;
                tspUtil(i, count + 1, cost + graph[pos][i], start);
                visited[i] = false;  // backtrack
            }
        }
    }

public:
    TSP(const vector<vector<int>>& g) : graph(g), V(g.size()) {
        visited = vector<bool>(V, false);
        minCost = INT_MAX;
    }

    int findShortestTour() {
        visited[0] = true;
        tspUtil(0, 1, 0, 0);
        return minCost;
    }
};

int main() {
    vector<vector<int>> graph = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    TSP tsp(graph);
    cout << "Minimum TSP tour cost: " << tsp.findShortestTour() << endl;

    return 0;
}
