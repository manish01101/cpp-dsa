#include<bits/stdc++.h>
using namespace std;

/*
1 to n
=> take i as root node
=> (i-1) left part & (n-i) right part

=> f(n) = sum[f(i-1) * f(n-i)]  for all i
*/

int solve(int n) {
	if (n <= 1)
		return 1;

	int ans = 0;
	// let i as root node
	for (int i = 1; i <= n; i++) {
		ans += solve(i - 1) * solve(n - i);
	}
	return ans;
}
int solveMem(int n, vector<int>& dp) {
	if (n <= 1)
		return 1;
	if (dp[n] != -1)
		return dp[n];

	int ans = 0;
	for (int i = 1; i <= n; i++) {
		ans += solveMem(i - 1, dp) * solveMem(n - i, dp);
	}
	return dp[n] = ans;
}
int solveTab(int n) {
	vector<int> dp(n + 1, 0);
	// base case handle
	dp[0] = dp[1] = 1;

	for (int num = 2; num <= n; num++) {
		// i=> root node
		for (int i = 1; i <= num; i++) {
			dp[num] += dp[i - 1] * dp[num - i];
		}
	}
	return dp[n];
}
int numTrees(int n) {
	/* -- rec -- */
	// return solve(n);

	/* -- rec + mem -- */
	// vector<int> dp(n + 1, -1);
	// return solveMem(n, dp);

	/* -- tabulation -- */
	return solveTab(n);
}