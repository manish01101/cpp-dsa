#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Graph {
public:
    int V;
    vector<vector<int>> adj;

    Graph(int V);
    void addEdge(int u, int v);
    vector<int> greedyColoring();
    void printColoring(const vector<int>& colors);
};

// Constructor
Graph::Graph(int V) {
    this->V = V;
    adj.resize(V);
}

// Add an undirected edge
void Graph::addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

// Greedy coloring algorithm
vector<int> Graph::greedyColoring() {
    vector<int> colors(V, -1);  // -1 means no color assigned
    colors[0] = 0;              // Assign the first color to the first vertex

    // To keep track of available colors
    vector<bool> available(V, true);

    // Assign colors to remaining V-1 vertices
    for (int u = 1; u < V; u++) {
        fill(available.begin(), available.end(), true);
        // Mark colors of adjacent vertices as unavailable
        for (int neighbor : adj[u]) {
            if (colors[neighbor] != -1)
                available[colors[neighbor]] = false;
        }

        // Find the first available color
        int cr;
        for (cr = 0; cr < V; cr++) {
            if (available[cr])
                break;
        }

        colors[u] = cr; // Assign the found color
    }

    return colors;
}

// Print the result
void Graph::printColoring(const vector<int>& colors) {
    cout << "Vertex\tColor\n";
    for (int i = 0; i < V; i++) {
        cout << i << "\t" << colors[i] << endl;
    }
}

// Main function to test
int main() {
    Graph g(5);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(3, 4);

    vector<int> coloring = g.greedyColoring();
    g.printColoring(coloring);

    return 0;
}







// #include <iostream>
// #include <vector>
// using namespace std;

// // Function to check if the current color assignment is safe for vertex
// bool isSafe(int v, vector<vector<int>>& graph, vector<int>& color, int c) {
// 	for (int i = 0; i < graph.size(); i++) {
// 		if (graph[v][i] && color[i] == c)
// 			return false;
// 	}
// 	return true;
// }

// // Recursive utility function to solve m coloring problem
// bool graphColoringUtil(vector<vector<int>>& graph, int m, vector<int>& color, int v) {
// 	if (v == graph.size())
// 		return true;

// 	for (int c = 1; c <= m; c++) {
// 		if (isSafe(v, graph, color, c)) {
// 			color[v] = c;
// 			if (graphColoringUtil(graph, m, color, v + 1))
// 				return true;
// 			color[v] = 0;
// 		}
// 	}
// 	return false;
// }

// // Main function to solve the m Coloring problem
// bool graphColoring(vector<vector<int>>& graph, int m) {
// 	vector<int> color(graph.size(), 0);
// 	if (!graphColoringUtil(graph, m, color, 0)) {
// 		cout << "Solution does not exist\n";
// 		return false;
// 	}

// 	cout << "Solution Exists: Following are the assigned colors:\n";
// 	for (int i = 0; i < color.size(); i++)
// 		cout << "Vertex " << i << " --->  Color " << color[i] << endl;
// 	return true;
// }

// /*
// Algorithm Steps (Graph Coloring using Backtracking):

// 1. Start with the first vertex and assign the first color.
// 2. For each vertex, try all available colors (from 1 to m).
// 3. For each color, check if it is safe to assign (no adjacent vertex has the same color).
// 4. If safe, assign the color and move to the next vertex recursively.
// 5. If all vertices are assigned a color, print the solution.
// 6. If no color can be assigned to a vertex, backtrack and try a different color for the previous vertex.
// 7. If no solution exists, report failure.
// */

// int main() {
// 	// Example graph (adjacency matrix)
// 	vector<vector<int>> graph = {
// 		{0, 1, 1, 1},
// 		{1, 0, 1, 0},
// 		{1, 1, 0, 1},
// 		{1, 0, 1, 0}
// 	};
// 	int m = 3; // Number of colors
// 	graphColoring(graph, m);
// 	return 0;
// }
