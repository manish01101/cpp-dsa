
#include<iostream>
#include<vector>
using namespace std;

// USING RECURSION ONLY
int solve(vector<int> &cost, int n) {
    // base case
    if(n == 0 || n == 1) return n;
    int ans = cost[n] + min(solve(cost, n-1), solve(cost, n-2));
    return ans;
}
int minCostClimbingStairs(vector<int> &cost) {
    int n = cost.size();
    int ans = min(solve(cost, n-1), solve(cost, n-2));
    return ans;
}



// USING RECURSION + MEMOIZATION : TOP-DOWN APPROACH
// TC - O(n), SC - O(n)+O(n)
int solve2(vector<int> &cost, int n, vector<int> &dp) {
    // base case
    if(n == 0 || n == 1) return n;
    // step 3 : using memoization
    if(dp[n] != -1) return dp[n];
    // step 2
    dp[n] = cost[n] + min(solve2(cost, n-1, dp), solve2(cost, n-2, dp));
    return dp[n];
}
int minCostClimbingStairs(vector<int> &cost) {
    int n = cost.size();
    // step 1 - creating dp arr
    vector<int> dp(n+1, -1);
    int ans = min(solve2(cost, n-1, dp), solve2(cost, n-2, dp));
    return ans;
}



// TABULATION METHOD : BOTTON-UP APPROACH
// TC - O(n), SC - O(n)
int solve3(vector<int> &cost, int n) {
    // step 1 : creating dp arr
    vector<int> dp(n+1);
    // step 2: base case analyze
    dp[0] = cost[0];
    dp[1] = cost[1];
    // step 3: find next ans using prev base case
    for(int i=2; i<n; i++) {
        dp[i] = cost[i] + min(dp[i-1], dp[i-2]);
    }
    return min(dp[n-1], dp[n-2]);
}
int minCostClimbingStairs(vector<int> &cost) {
    int n = cost.size();
    return solve3(cost, n);
}



// SPACE OPTIMIZATION
// TC - O(n), SC - O(1)
int solve4(vector<int> &cost, int n) {
    // base case
    int prev1 = cost[1];
    int prev2 = cost[0];
    // finding next using base case
    for(int i=2; i<n; i++) {
        int curr = cost[i] + min(prev1, prev2);
        prev2 = prev1;
        prev1 = curr;
    }
    return min(prev1, prev2);
}
int minCostClimbingStairs(vector<int> &cost) {
    int n = cost.size();
    return solve3(cost, n);
}