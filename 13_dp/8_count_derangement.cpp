#include<bits/stdc++.h>
using namespace std;
#define MOD 1000000007
/*
total way of placing an ele = (n-1) * sol of subproblem
2 possibilities
	-> both i & 0 index ele swapped => (n-2) index available & (n-2) num to be placed => f(n-2)
	-> single ele i.e 0 idx val is placed in i'th index => (n-1)index available for i'th val & n-1 num to be placed => f(n-1)

=> f(n) = (n-1)*[f(n-2) + f(n-1)]
*/
long long int solve(int n) {
	// base case
	if (n == 1)
		return 0;
	if (n == 2)
		return 1;

	long long int ans = (((n - 1) % MOD) * ((solve(n - 1) % MOD + solve(n - 2)) % MOD)) % MOD;

	return ans;
}
long long int solveMem(int n, vector<long long int>& dp) {
	// base case
	if (n == 1)
		return 0;
	if (n == 2)
		return 1;
	// if val is present in dp
	if (dp[n] != -1)
		return dp[n];

	// store val in dp
	dp[n] = (((n - 1) % MOD) * ((solveMem(n - 1, dp) % MOD + solveMem(n - 2, dp)) % MOD)) % MOD;

	return dp[n];
}
long long solveTab(int n) {
	vector<long long int> dp(n + 1, 0);
	dp[1] = 0;
	dp[2] = 1;

	for (int i = 3; i <= n; i++) {
		long long int first = dp[i - 1] % MOD;
		long long int second = dp[i - 2] % MOD;

		long long int sum = (first + second) % MOD;
		long long int ans = ((i - 1) * sum) % MOD;
		dp[i] = ans;
	}
	return dp[n];
}
long long solveSpaceOpt(int n) {
	int prev2 = 0;
	int prev1 = 1;

	for (int i = 3; i <= n; i++) {
		long long int first = prev1 % MOD;
		long long int second = prev2 % MOD;

		long long int sum = (first + second) % MOD;
		long long int  ans = ((i - 1) * sum) % MOD;

		prev2 = prev1;
		prev1 = ans;
	}
	return prev1;
}

long long int countDerangement(int n) {
	/* --- recursion --- */
	// long long int ans = solve(n);

	/* --- rec + mem --- */
	// vector<long long int> dp(n + 1, -1);
	// long long int ans = solveMem(n, dp);

	/* ---- tabulation ---- */
	long long int ans = solveTab(n);

	return ans;
}