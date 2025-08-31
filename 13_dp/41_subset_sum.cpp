
#include <bits/stdc++.h>
using namespace std;

// Function to check if there is a subset with the given sum
//  using recursion
bool isSubsetSumRec(vector<int>& arr, int n, int sum) {

	// Base Cases
	if (sum == 0)
		return true;
	if (n == 0)
		return false;

	// If last element is greater than sum, then ignore it
	if (arr[n - 1] > sum)
		return isSubsetSumRec(arr, n - 1, sum);

	// Check if sum can be obtained by including or excluding the last element
	return isSubsetSumRec(arr, n - 1, sum) || isSubsetSumRec(arr, n - 1, sum - arr[n - 1]);
}


// using memoization

bool isSubsetSumMem(vector<int>& arr, int n, int sum,
	vector<vector<int>>& memo) {

	// If the sum is zero, we found a subset
	if (sum == 0)
		return 1;

	// If no elements are left
	if (n <= 0)
		return 0;

	// If the value is already computed, return it
	if (memo[n][sum] != -1)
		return memo[n][sum];

	// If the last element is greater than the sum, ignore it
	if (arr[n - 1] > sum)
		return memo[n][sum] = isSubsetSumMem(arr, n - 1, sum, memo);
	else { // Include or exclude the last element
		return memo[n][sum] = isSubsetSumMem(arr, n - 1, sum, memo) || isSubsetSumMem(arr, n - 1, sum - arr[n - 1], memo);
	}
}


// using tabulation
bool isSubsetSumTab(vector<int>& arr, int sum) {
	int n = arr.size();

	// Create a 2D vector for storing results of subproblems
	vector<vector<bool>> dp(n + 1, vector<bool>(sum + 1, false));

	// If sum is 0, then answer is true (empty subset)
	for (int i = 0; i <= n; i++)
		dp[i][0] = true;

	// Fill the dp table in bottom-up manner
	for (int i = 1; i <= n; i++) {

		for (int j = 1; j <= sum; j++) {
			if (j < arr[i - 1]) {
				// Exclude the current element
				dp[i][j] = dp[i - 1][j];
			}
			else {
				// Include or exclude
				dp[i][j] = dp[i - 1][j]
					|| dp[i - 1][j - arr[i - 1]];
			}
		}
	}

	return dp[n][sum];
}



// Space Optimized Dynamic Programming
bool isSubsetSumSpcOpt(vector<int> arr, int sum) {
	int n = arr.size();
	vector<bool> prev(sum + 1, false), curr(sum + 1);

	// Mark prev[0] = true as it is true to make sum = 0 using 0 elements
	prev[0] = true;

	// Fill the subset table in bottom up manner
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= sum; j++) {
			if (j < arr[i - 1])
				curr[j] = prev[j];
			else
				curr[j] = (prev[j] || prev[j - arr[i - 1]]);
		}
		prev = curr;
	}
	return prev[sum];
}

int main() {
	vector<int> arr = { 3, 34, 4, 12, 5, 2 };
	int sum = 9;
	int n = arr.size();

	// bool ans = isSubsetSumRec(arr, n, sum);

	// vector<vector<int>> memo(n + 1, vector<int>(sum + 1, -1));
	// bool ans =  isSubsetSumMem(arr, n, sum, memo);

	// bool ans = isSubsetSumTab(arr, sum);

	bool ans = isSubsetSumSpcOpt(arr, sum);

	if (ans)
		cout << "True";
	else
		cout << "False";
	return 0;
}
