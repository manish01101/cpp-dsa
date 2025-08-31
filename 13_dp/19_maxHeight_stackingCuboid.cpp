#include<bits/stdc++.h>
using namespace std;

/*
cuboid (l, b, h)
sort all dimension for every cuboid, so last index ele is max, that will be height
again sort cuboid on the basis of l & b, last cuboid will be bigger
use longest increasing subseq. logic
*/
class Solution {
	bool check(vector<int>& base, vector<int>& newBox) {
		if (newBox[0] <= base[0] and newBox[1] <= base[1] and newBox[2] <= base[2]) {
			return true;
		}
		return false;
	}
	int solveMem(int n, vector<vector<int>>& cuboids, int curr, int prev, vector<vector<int>>& dp) {
		if (curr == n)
			return 0;
		if (dp[curr][prev + 1] != -1) {
			return dp[curr][prev + 1];
		}

		int incl = 0;
		if (prev == -1 or check(cuboids[curr], cuboids[prev])) {
			incl = cuboids[curr][2] + solveMem(n, cuboids, curr + 1, curr, dp);
		}
		int excl = solveMem(n, cuboids, curr + 1, prev, dp);
		return dp[curr][prev + 1] = max(incl, excl);
	}

	int solveTab(int n, vector<vector<int>>& cuboids) {
		vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

		for (int curr = n - 1; curr >= 0; --curr) {
			for (int prev = curr - 1; prev >= -1; --prev) {
				int incl = 0;
				if (prev == -1 or check(cuboids[curr], cuboids[prev])) {
					incl = cuboids[curr][2] + dp[curr + 1][curr + 1];
				}
				int excl = dp[curr + 1][prev + 1];
				dp[curr][prev + 1] = max(incl, excl);
			}
		}
		return dp[0][0];
	}
	int solveSpcOpt(int n, vector<vector<int>>& cuboids) {
		vector<int> currRow(n + 1, 0);
		vector<int> nextRow(n + 1, 0);

		for (int curr = n - 1; curr >= 0; curr--) {
			for (int prev = curr - 1; prev >= -1; prev--) {
				int incl = 0;
				if (prev == -1 or check(cuboids[curr], cuboids[prev])) {
					incl = cuboids[curr][2] + nextRow[curr + 1]; // curr+1->pass updated prev val+1 for +ve index
				}
				int excl = nextRow[prev + 1];

				currRow[prev + 1] = max(incl, excl);
			}
			nextRow = currRow;
		}
		return nextRow[0];
	}
public:
	int maxHeight(vector<vector<int>>& cuboids) {
		int n = cuboids.size();
		// apply greedy algo to maximize the height, sort ele of every cuboid and choose 3rd ele as height
		for (auto& cuboid : cuboids) {
			sort(cuboid.begin(), cuboid.end());
		}

		// sort cuboids ele-> now max base area(l*b) is at last
		sort(cuboids.begin(), cuboids.end());

		// apply longest increasing subseq
		
		// vector<vector<int>> dp(n, vector<int>(n + 1, -1));
		// return solveMem(n, cuboids, 0, -1, dp);

		// return solveTab(n, cuboids);

		// return solveSpcOpt(n, cuboids);
	}
};