#include<bits/stdc++.h>
using namespaces std;

/*
sol(i,j) = v[i]*v[k]*v[j] + solve(i,k) + solve(k, j)
*/
class Solution {
private:
	int solveRec(int i, int j, vector<int>& values) {
		if (i + 1 == j)
			return 0;

		int ans = INT_MAX;
		// solve for rest vertices
		for (int k = i + 1; k < j; k++) {
			int currAns = values[i] * values[j] * values[k] + solveRec(i, k, values) + solveRec(k, j, values);
			ans = min(ans, currAns);
		}

		return ans;
	}
	int solveMem(int i, int j, vector<int>& values, vector<vector<int>>& dp) {
		if (i + 1 == j)
			return 0;
		if (dp[i][j] != -1)
			return dp[i][j];

		int ans = INT_MAX;
		for (int k = i + 1; k < j; k++) {
			int currAns = values[i] * values[j] * values[k] + solveMem(i, k, values, dp) + solveMem(k, j, values, dp);
			ans = min(ans, currAns);
			dp[i][j] = ans;
		}
		return dp[i][j];
	}
	int solveTab(vector<int>& values) {
		int n = values.size();
		vector<vector<int>> dp(n, vector<int>(n, 0));

		for (int i = n - 1; i >= 0; i--) {
			for (int j = i + 2; j < n; j++) { // j starts from i+2 to ensure a valid polygon
				int ans = INT_MAX;
				for (int k = i + 1; k < j; k++) {
					int currAns = values[i] * values[j] * values[k] + dp[i][k] + dp[k][j];
					ans = min(ans, currAns);
				}
				dp[i][j] = ans;
			}
		}
		return dp[0][n - 1];
	}
public:
	int minScoreTriangulation(vector<int>& values) {
		int n = values.size();
		// recursion
		// return solveRec(0, n-1, values);

		// rec+mem -> top-down dp
		// vector<vector<int>> dp(n, vector<int>(n, -1));
		// return solveMem(0, n-1, values, dp);

		// tabulation -> bottom-up dp
		return solveTab(values);
	}
};