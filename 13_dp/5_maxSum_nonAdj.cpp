#include<bits/stdc++.h>
using namespace std;

/*
include => i = i+2
exclude => i = i+1
*/

int solveRec(vector<int>& nums, int n) {
	// base case
	if (n < 0)
		return 0;
	if (n == 0)
		return nums[0];
	int incl = solveRec(nums, n - 2) + nums[n];
	int excl = solveRec(nums, n - 1) + 0;

	return max(incl, excl);
}
int solveMem(vector<int>& nums, int n, vector<int>& dp) {
	// base case
	if (n < 0)
		return 0;
	if (n == 0)
		return nums[0];
	// check if val is in dp
	if (dp[n] != -1)
		return dp[n];

	int incl = solveMem(nums, n - 2, dp) + nums[n];
	int excl = solveMem(nums, n - 1, dp) + 0;
	// store in dp
	dp[n] = max(incl, excl);
	return dp[n];
}
int solveTab(vector<int>& nums, int n) {
	vector<int> dp(n, 0);
	// base case analyze
	dp[0] = nums[0];

	for (int i = 1; i < n; i++) {
		int incl = dp[i - 2] + nums[i];
		int excl = dp[i - 1] + 0;
		dp[n] = max(incl, excl);
	}
	return dp[n - 1];
}
int solveSpaceOpt(vector<int>& nums, int n) {
	int prev2 = 0;
	int prev1 = nums[0];

	for (int i = 1; i < n; i++) {
		int incl = prev2 + nums[i];
		int excl = prev1 + 0;
		int curr = max(incl, excl);
		prev2 = prev1;
		prev1 = curr;
	}
	return prev1;
}
int maxiNodeAdjSum(vector<int>& nums) {
	int n = nums.size();
	/* -- REC -- */
	// int ans = solveRec(nums, n-1);

	/* -- REC + MEM -- */
	// vector<int> dp(n, -1);
	// int ans = solveMem(nums, n - 1, dp);

	/* --- Tabulation ---- */
	// int ans = solveTab(nums, n-1);

	/*  --- SPACE OPTI ----*/
	int ans = solveSpaceOpt(nums, n - 1);

	return ans;
}