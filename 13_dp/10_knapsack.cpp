#include<bits/stdc++.h>
using namespace std;

/*
thief -> knapsack -> can carry at max weight W
n items
1	2	3 	4 		n
w1  w2  w3  w4  	wn (weight)
v1  v2  v3  v4      vn (value)
find max val with weight W
*/

int solve(vector<int>& weight, vector<int>& value, int index, int capacity) {
	// base case
	// if only 1 item to steal, then just compare its weight with the knapsack capacity
	if (index == 0) {
		if (weight[index] <= capacity)
			return value[index];
		else
			return 0;
	}

	// include
	int include = 0;
	if (weight[index] <= capacity) {
		include = value[index] + solve(weight, value, index - 1, capacity - weight[index]);
	}
	// exclude
	int exclude = 0 + solve(weight, value, index - 1, capacity);

	// choose max value
	int ans = max(include, exclude);
	return ans;
}

int ks(int wt[], int profit[], int w, int n) {
	if (w == 0 or n == 0) return 0; // base
	if (wt[n] > w) return ks(wt, profit, w, n - 1); //skip
	else return max(ks(wt, profit, w, n - 1), profit[n] + ks(wt, profit, w - wt[n], n - 1));
}


/* RECURSION + MEMOIZATION */
int solveMem(vector<int>& weight, vector<int>& value, int index, int capacity, vector<vector<int>>& dp) {
	// base case
	if (index == 0) {
		if (weight[0] <= capacity)
			return value[0];
		else
			return 0;
	}
	// if val present in dp
	if (dp[index][capacity] != -1)
		return dp[index][capacity];

	// process
	int include = 0;
	if (weight[index] <= capacity) {
		include = value[index] + solveMem(weight, value, index - 1, capacity - weight[index], dp);
	}
	int exclude = 0 + solveMem(weight, value, index - 1, capacity, dp);

	// store in dp
	dp[index][capacity] = max(include, exclude);

	return dp[index][capacity];
}

/* TABULAITON */
int solveTab(vector<int>& weight, vector<int>& value, int n, int capacity) {
	// Step 1: Create DP table
	vector<vector<int>> dp(n, vector<int>(capacity + 1, 0));

	// Step 2: Base Case
	// for (int w = weight[0]; w <= capacity; w++) {
	// 	if (weight[0] <= capacity)
	// 		dp[0][w] = value[0];
	// 	else
	// 		dp[0][w] = 0;
	// }
	for (int w = 0; w <= capacity; w++) {
		if (weight[0] <= w)
			dp[0][w] = value[0];
	}

	// Step 3: Process remaining items
	for (int index = 1; index < n; index++) {
		for (int wt = 0; wt <= capacity; wt++) {
			int include = 0;
			if (weight[index] <= wt)
				include = value[index] + dp[index - 1][wt - weight[index]];

			int exclude = dp[index - 1][wt];

			dp[index][wt] = max(include, exclude);
		}
	}
	return dp[n - 1][capacity];
}

/* SPACE OPTIMISATION */
int solveSpaceOpt(vector<int>& weight, vector<int>& value, int n, int capacity) {
	// step 1: 
	vector<int> prev(capacity + 1, 0);
	vector<int> curr(capacity + 1, 0);

	// step 2: analyze vase case
	for (int w = weight[0]; w <= capacity; w++) {
		if (weight[0] <= capacity)
			prev[w] = value[0];
		else
			prev[w] = 0;
	}
	// Step 3: Process remaining items
	for (int index = 1; index < n; index++) {
		for (int wt = 0; wt <= capacity; wt++) {
			int include = 0;
			if (weight[index] <= wt)
				include = value[index] + prev[wt - weight[index]];

			int exclude = 0 + prev[wt];

			curr[wt] = max(include, exclude);
		}
		prev = curr;
	}
	return prev[capacity];
}

/* SPACE OPTIMISATION 2 */
int solveSpaceOpt2(vector<int>& weight, vector<int>& value, int n, int capacity) {
	// step 1: 
	vector<int> curr(capacity + 1, 0);

	// step 2: analyze vase case
	for (int w = weight[0]; w <= capacity; w++) {
		if (weight[0] <= capacity)
			curr[w] = value[0];
		else
			curr[w] = 0;
	}
	// Step 3: Process remaining items
	for (int index = 1; index < n; index++) {
		for (int wt = capacity; wt >= 0; wt--) {
			int include = 0;
			if (weight[index] <= wt)
				include = value[index] + curr[wt - weight[index]];

			int exclude = 0 + curr[wt];

			curr[wt] = max(include, exclude);
		}
	}
	return curr[capacity];
}

// Space Optimization (O(capacity))
int knapsackOptimized(vector<int>& weight, vector<int>& value, int n, int capacity) {
	vector<int> dp(capacity + 1, 0);

	for (int i = 0; i < n; i++) {
		for (int w = capacity; w >= weight[i]; w--) {
			dp[w] = max(dp[w], value[i] + dp[w - weight[i]]);
		}
	}

	return dp[capacity];
}


int knapsack(vector<int> weight, vector<int> value, int n, int maxWeight) {
	/* --- recursion --- */
	// return solve(weight, value, n - 1, maxWeight);

	/* --- rec + mem --- */
	// vector<vector<int>> dp(n, vector<int>(maxWeight + 1, -1));
	// return solveMem(weight, value, n - 1, maxWeight, dp);

	/* --- tabulation ---- */
	// return solveTab(weight, value, n, maxWeight);

	/* --- space optimisation --- */
	return solveSpaceOpt(weight, value, n, maxWeight);
}