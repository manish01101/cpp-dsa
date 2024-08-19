#include<iostream>
#include<unordered_map>
#include<list>
#include<set>
#include<stack>
#include<algorithm>
#include<vector>
#include<limits.h>
using namespace std;

/*
bellman ford algo work on -ve weight
this algo dont work on -ve cycle => using this we can find -ve cycle is present or not

TC: O(nodes * edges)
*/

int bellmonFord(int n, int m, int src, int dest, vector<vector<int>>& edges) {

	vector<int> dist(n + 1, 1e9);
	dist[src] = 0;

	// STEP 1: apply n-1 times distance minimization formula on each node 
	for (int i = 1; i <= n; i++) {
		// traverse on edge list
		for (int j = 0; j < m; j++) {
			int u = edges[j][0];
			int v = edges[j][1];
			int wt = edges[j][2];
			// distance minimization formula
			if (dist[u] != 1e9 && (dist[u] + wt) < dist[v]) {
				dist[v] = dist[u] + wt;
			}
		}
	}

	// STEP 2: check for negative cycle
	// if any dist will update -> means -ve cycle present => can't find shortest path
	bool flag = false;
	for (int i = 1; i <= n; i++) {
		// traverse on edge list
		for (int j = 0; j < m; j++) {
			int u = edges[j][0];
			int v = edges[j][1];
			int wt = edges[j][2];

			if (dist[u] != 1e9 && (dist[u] + wt) < dist[v]) {
				flag = true;
			}
		}
	}
	if (flag == false) { // no -ve cycle
		return dist[dest];
	}
	return -1;
}