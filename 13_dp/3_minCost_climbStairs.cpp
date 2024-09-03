#include<iostream>
#include<vector>
using namespace std;

// using only recursion
int solve(vector<int>& cost, int n) {
	// base case
	if (n == 0) {
		return cost[0];
	}
	if (n == 1) {
		return cost[1];
	}
	int ans = cost[n] + min(solve(cost, n - 1), solve(cost, n - 2));
	return ans;
}

// using recursion + memoization: TOP DOWN
int solve2(vector<int>& cost, int n, vector<int>& dp) {
	// base case
	if (n == 0 || n == 1) {
		return cost[n];
	}
	// step 3: check memoized value
	if (dp[n] != -1) {
		return dp[n];
	}
	// step 2: store in dp
	dp[n] = cost[n] + min(solve2(cost, n - 1, dp), solve2(cost, n - 2, dp));
	return dp[n];
}

// tabulation: BOTTOM UP APPROACH
int solve3(vector<int>& cost, int n) {
	// step 1: creation of dp arr
	vector<int> dp(n + 1);
	// step 2: base case analyze
	dp[0] = cost[0];
	dp[1] = cost[1];

	// step 3:
	for (int i = 2; i < n; i++) {
		dp[i] = cost[i] + min(dp[i - 1], dp[i - 2]);
	}
	return min(dp[n - 1], dp[n - 2]);
}

// space optimisation
int solve4(vector<int>& cost, int n) {
	int prev1 = cost[1];
	int prev2 = cost[0];

	for (int i = 2; i < n; i++) {
		int curr = cost[i] + min(prev1, prev2);
		prev2 = prev1;
		prev1 = curr;
	}
	return min(prev1, prev2);
}


int minCostClimbingStairs(vector<int>& cost) {
	int n = cost.size();
	/* not adding cost of final stair, as we reach there */

	/* USING ONLY RECURSION */
	// int ans = min(solve(cost, n-1), solve(cost, n-2));
	// return ans;

	/* USING REC + MEM : TOP DOWN APPROACH */
	// step 1: create dp arr
	// vector<int> dp(n + 1, -1);
	// int ans = min(solve2(cost, n - 1, dp), solve2(cost, n - 2, dp));
	// return ans;

	/* BOTTOM UP APPROACH */
	// return solve3(cost, n);

	/* SPACE OPTIMISATION */
	return solve4(cost, n);
}