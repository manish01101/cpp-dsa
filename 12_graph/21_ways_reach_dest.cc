class Solution {
	using ll = long long;
	using pll = pair<ll, ll>;
	constexpr int MOD = 1e9 + 7;

public:
	int countPaths(int n, vector<vector<int>>& roads) {
		// creating adj list, since nodes are in range 0 to n-1=>used vector(index as nodes)
		vector<vector<pll>> adj(n); // {u, v, w}
		for (auto& road : roads) {
			int u = road[0];
			int v = road[1];
			int w = road[2];

			adj[u].push_back({ v, w });
			adj[v].push_back({ u, w });
		}

		// dijkstra algo with tracking of total ways with min cost
		priority_queue<pll, vector<pll>, greater<pll>> minHeap;
		vector<bool> isVisited(n, false);
		vector<ll> countWays(n, 0);
		vector<ll> minCost(n, LONG_MAX);

		int src = 0;
		minHeap.push({ 0, src }); // {cost, node}
		countWays[src] = 1;
		minCost[src] = 0;

		while (!minHeap.empty()) {
			pll curr = minHeap.top(); minHeap.pop();
			ll currCost = curr.first;
			ll currNode = curr.second;

			if (isVisited[currNode])
				continue;

			isVisited[currNode] = true;
			for (auto& [nbrNode, nbrWeight] : adj[currNode]) {
				if (!isVisited[nbrNode]) {
					if (currCost + nbrWeight < minCost[nbrNode]) {
						minCost[nbrNode] = currCost + nbrWeight;
						countWays[nbrNode] = countWays[currNode];
						minHeap.push({ minCost[nbrNode], nbrNode });
					}
					else if (currCost + nbrWeight == minCost[nbrNode]) {
						countWays[nbrNode] = (countWays[nbrNode] + countWays[currNode]) % MOD;
					}
				}
			}
		}
		return countWays[n - 1];
	}
};