#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>
using namespace std;

// Held-Karp algorithm for TSP (Dynamic Programming)
// Assumes 0-based indexing for cities

double heldKarp(const vector<vector<double>>& dist) {
	int n = dist.size();
	int N = 1 << n; // Total number of subsets
	vector<vector<double>> dp(N, vector<double>(n, numeric_limits<double>::infinity()));

	// Base case: start at city 0
	dp[1][0] = 0;

	// Iterate over all subsets of nodes
	for (int mask = 1; mask < N; ++mask) {
		for (int u = 0; u < n; ++u) {
			if (!(mask & (1 << u))) continue; // u not in subset
			for (int v = 0; v < n; ++v) {
				if (u == v || !(mask & (1 << v))) continue;
				dp[mask][u] = min(dp[mask][u], dp[mask ^ (1 << u)][v] + dist[v][u]);
			}
		}
	}

	// Find minimum cost to return to start
	double res = numeric_limits<double>::infinity();
	for (int u = 1; u < n; ++u) {
		res = min(res, dp[N - 1][u] + dist[u][0]);
	}
	return res;
}

int main() {
	// Example: 4 cities, symmetric distances
	vector<vector<double>> dist = {
		{0, 10, 15, 20},
		{10, 0, 35, 25},
		{15, 35, 0, 30},
		{20, 25, 30, 0}
	};

	double min_cost = heldKarp(dist);
	cout << "Minimum tour cost: " << min_cost << endl;
	return 0;
}
