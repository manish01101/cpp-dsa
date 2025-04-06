#include<bits/stdc++.h>
using namespace std;


/*
step 1: insert -1 at begining for both arr
if ele is strictly greater than previous one => no swap
else => swap
*/

int solve(vector<int>& nums1, vector<int>& nums2, int index, bool isSwapped) {
	// base case
	if (index == nums1.size())
		return 0;

	int ans = INT_MAX;

	int prev1 = nums1[index - 1];
	int prev2 = nums2[index - 1];

	// this is because we don't swap ele actually, so we swap here to find actual prev ele
	if (isSwapped)
		swap(prev1, prev2);

	// noswap
	if (nums1[index] > prev1 && nums2[index] > prev2) {
		ans = solve(nums1, nums2, index + 1, false);
	}
	// swap
	if (nums1[index] > prev2 && nums1[index] > prev1) {
		ans = min(ans, 1 + solve(nums1, nums2, index + 1, true));
	}
	return ans;
}


int solveMem(vector<int>& nums1, vector<int>& nums2, int index, bool isSwapped, vector<vector<int>>& dp) {
	// base case
	if (index == nums1.size())
		return 0;
	if (dp[index][isSwapped] != -1)
		return dp[index][isSwapped];

	int ans = INT_MAX;

	int prev1 = nums1[index - 1];
	int prev2 = nums2[index - 1];

	// this is because we don't swap ele actually, so we swap here to find actual prev ele
	if (isSwapped)
		swap(prev1, prev2);

	// noswap
	if (nums1[index] > prev1 && nums2[index] > prev2) {
		ans = solveMem(nums1, nums2, index + 1, false, dp);
	}
	// swap
	if (nums1[index] > prev2 && nums1[index] > prev1) {
		ans = min(ans, 1 + solveMem(nums1, nums2, index + 1, true, dp));
	}
	return dp[index][isSwapped] = ans;
}

int solveTab(vector<int>& nums1, vector<int>& nums2) {
	int n = nums1.size();
	vector<vector<int>> dp(n + 1, vector<int>(2, 0));

	for (int index = n - 1; index >= 1; index--) {
		for (int isSwapped = 1; isSwapped >= 0; isSwapped--) {

			int ans = INT_MAX;
			int prev1 = nums1[index - 1];
			int prev2 = nums2[index - 1];

			// this is because we don't swap ele actually, so we swap here to find actual prev ele
			if (isSwapped)
				swap(prev1, prev2);

			// noswap
			if (nums1[index] > prev1 && nums2[index] > prev2) {
				ans = dp[index + 1][false];
			}
			// swap
			if (nums1[index] > prev2 && nums1[index] > prev1) {
				ans = min(ans, 1 + dp[index + 1][true]);
			}
			dp[index][isSwapped] = ans;
		}
	}
	return dp[1][0];
}


int solveSpaceOpt(vector<int>& nums1, vector<int>& nums2) {
	int n = nums1.size();

	int Swap = 0;
	int noSwap = 0;
	int currSwap = 0;
	int currnoSwap = 0;

	for (int index = n - 1; index >= 1; index--) {
		for (int isSwapped = 1; isSwapped >= 0; isSwapped--) {

			int ans = INT_MAX;
			int prev1 = nums1[index - 1];
			int prev2 = nums2[index - 1];

			// catched when ele is equal to its prev
			if (isSwapped)
				swap(prev1, prev2);

			// noswap
			if (nums1[index] > prev1 && nums2[index] > prev2) {
				ans = noSwap;
			}
			// swap
			if (nums1[index] > prev2 && nums1[index] > prev1) {
				ans = min(ans, 1 + Swap);
			}

			if (isSwapped)
				currSwap = ans;
			else
				currnoSwap = ans;
		}
		Swap = currSwap;
		noSwap = currnoSwap;
	}
	return min(Swap, noSwap);
}



int solveSpaceOpt(vector<int>& nums1, vector<int>& nums2) {
	int n = nums1.size();

	// Initialize swap and no-swap for the first element
	int Swap = 1;      // We can swap the first element (so the cost is 1)
	int noSwap = 0;    // We don't swap the first element (so the cost is 0)

	for (int index = 1; index < n; index++) {
		int currSwap = INT_MAX;
		int currnoSwap = INT_MAX;

		// No swap at index 'i'
		if (nums1[index] > nums1[index - 1] && nums2[index] > nums2[index - 1]) {
			currnoSwap = noSwap;      // No need to swap
			currSwap = Swap + 1;      // Swap the current element based on the previous swap
		}
		// Swap at index 'i'
		if (nums1[index] > nums2[index - 1] && nums2[index] > nums1[index - 1]) {
			currnoSwap = min(currnoSwap, Swap);    // Swap the previous but no swap now
			currSwap = min(currSwap, noSwap + 1);  // No swap previously but swap now
		}
		// Update the states for the next iteration
		noSwap = currnoSwap;
		Swap = currSwap;
	}
	// The answer is the minimum swaps needed by either swapping or not swapping at the last index
	return min(Swap, noSwap);
}



int minSwap(vector<int>& nums1, vector<int>& nums2) {
	nums1.insert(nums1.begin(), -1);
	nums2.insert(nums2.begin(), -1);
	bool isSwapped = false; // shows that where prev indices were swapped or not
	int n = nums1.size();

	/* -- recursion -- */
	// return solve(nums1, nums2, 1, isSwapped);

	/* -- rec + mem -- */
	// vector<vector<int>> dp(n + 1, vector<int>(2, -1));
	// solveMem(nums1, nums2, 1, isSwapped, dp);

	/* -- tabulation -- */
	// return solveTab(nums1, nums2);

	/* -- space opt -- */
	return solveSpaceOpt(nums1, nums2);
}