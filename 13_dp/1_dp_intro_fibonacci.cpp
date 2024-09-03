/*
top down => recursion + memoization
botton up => tabulation
space optimization
*/

#include<iostream>
#include<vector>
using namespace std;


/* fibonacci no=> TOP DOWN: tc: O(N), sc: O(2N)
step 1: create dpArr
step 2: store ans;
step 3: check memoized val if present
*/
int fibTopDown(int n, vector<int>& dp) {
	// base case
	if (n <= 1)
		return n;
	// step 3
	if (dp[n] != -1) {
		return dp[n];
	}
	// step 2
	dp[n] = fibTopDown(n - 1, dp) + fibTopDown(n - 2, dp);
	return dp[n];
}

/*
BOTTOM UP: tc: O(N), sc: O(N)
step 1: dp arr creation
step 2: base case
step 3: use prev val for finding next val
*/
int fibBottomUp(int n) {
	// step 1: 
	vector<int> dp(n + 1);
	// step 2:
	dp[0] = 0;
	dp[1] = 1;
	// step 3:
	for (int i = 2; i <= n; i++) {
		dp[i] = dp[i - 1] + dp[i - 2];
	}
	return dp[n];
}

/* SPACE OPTIMIZATION: tc: o(N), sc: O(1) */
int fibSpaceOpt(int n) {
	int prev1 = 1;
	int prev2 = 0;
	for (int i = 2; i <= n; i++) {
		int curr = prev1 + prev2;
		prev2 = prev1;
		prev1 = curr;
	}
	return prev1;
}
int main() {
	int n;
	cin >> n;
	// step 1
	vector<int> dp(n + 1, -1);

	int ans = fibTopDown(n, dp);
	cout << ans << endl;

	ans = fibBottomUp(n);
	cout << ans << endl;

	ans = fibSpaceOpt(n);
	cout << ans << endl;
}