class Solution {
	bool isSafe(int node, int col, vector<int>& color, vector<vector<int>>& adj) {
		for (int nbr : adj[node]) {
			if (color[nbr] == col) return false; // neighbor has same color
		}
		return true;
	}

	bool solve(int node, vector<int>& color, int m, int n, vector<vector<int>>& adj) {
		if (node == n) return true; // all vertices colored

		for (int col = 1; col <= m; col++) {
			if (isSafe(node, col, color, adj)) {
				color[node] = col;
				if (solve(node + 1, color, m, n, adj)) return true;
				color[node] = 0; 
			}
		}
		return false;
	}
public:
	bool graphColoring(int v, vector<vector<int>>& edges, int m) {
		// build adjacency list
		vector<vector<int>> adj(v);
		for (auto& ele : edges) {
			adj[ele[0]].push_back(ele[1]);
			adj[ele[1]].push_back(ele[0]);
		}

		vector<int> color(v, 0);
		return solve(0, color, m, v, adj);
	}
};
