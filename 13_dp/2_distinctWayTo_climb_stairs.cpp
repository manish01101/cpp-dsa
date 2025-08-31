#include<iostream>

using namespace std;

#define MOD 1000000007

// recursion
int solve(long long nStairs, int start) {
	// base case
	if (start == nStairs) {
		return 1;
	}
	if (start > nStairs) {
		return 0;
	}
	return (solve(nStairs, start + 1) + solve(nStairs, start + 2)) % MOD;
}
// rec + memoization
int solveMem(int start, int n, vector<int>& dp) {
	if (start == n)
		return 1;
	if (start > n)
		return 0;
	if (dp[start] != -1)
		return dp[start];
	return dp[start] = solveMem(start + 1, n, dp) + solveMem(start + 2, n, dp);
}
// tabulation - bottom-up approach
int solveTab(int n) {
	vector<int> dp(n + 2, 0);
	dp[n + 1] = 0;
	dp[n] = 1;
	for (int i = n - 1; i >= 0; i--) {
		dp[i] = dp[i + 1] + dp[i + 2];
	}
	return dp[0];
}
// space opt
int solveSpaceOpt(int n) {
	int prev2 = 0;
	int prev1 = 1;
	for (int i = n - 1; i >= 0; i--) {
		int curr = prev1 + prev2;
		prev2 = prev1;
		prev1 = curr;
	}
	return prev1;
}

// main fn
int countDistinctWayToClimbStair(long long nStairs) {
	// int ans = solve(nStairs, 0);

	// vector<int> dp(n + 1, -1);
	// int ans =  solveMem(0, n, dp);

	// int ans = solveTab(n);

	int ans = solveSpaceOpt(n);

	return ans;
}