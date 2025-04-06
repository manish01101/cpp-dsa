#include<bits/stdc++.h>
using namespace std;

int solve(int n, int a[], int curr, int prev) {
	// base case
	if (curr == n) {
		return 0;
	}
	// include
	int take = 0;
	if (prev == -1 || a[curr] > a[prev]) {
		take = 1 + solve(n, a, curr + 1, curr);
	}
	// exclude
	int notTake = 0 + solve(n, a, curr + 1, prev);
	return max(take, notTake);
}


/* curr => 0 to n-1 & prev => -1 to n-1 */
int solveMem(int n, int a[], int curr, int prev, vector<vector<int>>& dp) {
	// base case
	if (curr == n) {
		return 0;
	}
	if (dp[curr][prev + 1] != -1) { // prev+1 for handling index
		return dp[curr][prev];
	}
	// include
	int take = 0;
	if (prev == -1 || a[curr] > a[prev]) {
		take = 1 + solveMem(n, a, curr + 1, curr, dp);
	}
	// exclude
	int notTake = 0 + solveMem(n, a, curr + 1, prev, dp);
	return dp[curr][prev + 1] = max(take, notTake);
}


/* curr => n-1 to 0 & prev => n-1 to -1 */
int solveTab(int n, int a[]) {
	vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

	for (int curr = n - 1; curr >= 0; curr--) {
		for (int prev = curr - 1; prev >= -1; prev--) {
			// include
			int take = 0;
			if (prev == -1 || a[curr] > a[prev]) {
				take = 1 + dp[curr + 1][curr + 1]; // first curr+1 -> dp row size (n+1), & second curr+1 instead of curr for handling -ve idx
			}
			// exclude
			int notTake = 0 + dp[curr + 1][prev + 1];
			dp[curr][prev + 1] = max(take, notTake);
		}
	}
	return dp[0][0]; //dp[0][-1+1] , +1 for handling -ve index
}

int solveSpaceOpt(int n, int a[]) {
	vector<int> currRow(n + 1, 0);
	vector<int> nextRow(n + 1, 0);
	for (int curr = n - 1; curr >= 0; curr--) {
		for (int prev = curr - 1; prev >= -1; prev--) {
			// include
			int take = 0;
			if (prev == -1 || a[curr] > a[prev]) {
				take = 1 + nextRow[curr + 1];
			}
			// exclude
			int notTake = 0 + nextRow[prev + 1];
			currRow[prev + 1] = max(take, notTake);
		}
		nextRow = currRow;
	}
	return nextRow[0];
}

/* DP WITH BINARY SEARCH */
int solveOptimal(int n, int a[]) { // tc: nlogn, sc: n
	if (n == 0)
		return 0;

	vector<int> ans;
	ans.push_back(a[0]);

	for (int i = 1; i < n; i++) {
		if (a[i] > ans.back()) {
			ans.push_back(a[i]);
		}
		else {
			// find index of just greater ele
			int index = lower_bound(ans.begin(), ans.end(), a[i]) - ans.begin();
			ans[index] = a[i];
		}
	}
	return ans.size();
}
int longestSubsequence(int n, int a[]) {
	/* --- recursion --- */
	// return solve(n, a, 0, -1);

	/* -- rec + mem -- */
	// vector<vector<int>> dp(n, vector<int> (n+1, -1));
	// return solveMem(n, a, 0, -1, dp);

	/* --- bottom up --- */
	// return solveTab(n, a);

	/* --- space opt --- */
	// return solveSpaceOpt(n, a);

	/* -- optimal sol -- */
	return solveOptimal(n, a);
}



// russian doll envelop
static bool cmp(const vector<int>& a, const vector<int>& b) {
	if (a[0] == b[0]) {
		return a[1] > b[1];  // sort height in descending order if width is the same
	}
	return a[0] < b[0];  // sort width in ascending order
}


int russianDollEnvelopes(vector<vector<int>>& envelopes) {
	sort(envelopes.begin(), envelopes.end(), cmp);

	int n = envelopes.size();

	int height[n];
	for (int i = 0; i < n; i++) {
		height[i] = envelopes[i][1];
	}

	return solveOptimal(n, height);
}