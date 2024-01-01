#include<iostream>
#include<vector>
#include<limits.h>

using namespace std;
#define MOD 1000000007
#define lli long long int

// RECURSION
lli countDerangement(int n) {
  // base case
  if(n == 1) return 0;
  if(n == 2) return 1;

  int ans = ((n-1) % MOD) * (countDerangement(n-1)%MOD + countDerangement(n-2)%MOD) % MOD;
  return ans;
}


// RECURSION + MEMOIZATION
lli solveMem(int n, vector<lli> &dp) {
  // base case
  if(n == 1) return 0;
  if(n == 2) return 1;

  if(dp[n] != -1) return dp[n];

  dp[n] = ((n-1) % MOD) * (solveMem(n-1, dp)%MOD + solveMem(n-2, dp)%MOD) % MOD;
  return dp[n]; 
}


// TABULATION
lli solveTab(int n) {
  vector<lli> dp(n+1, 0);
  dp[1] = 0;
  dp[2] = 1;
  for(int i=3; i<=n; i++) {
    lli first = dp[i-1] % MOD;
    lli second = dp[i-2] % MOD;
    lli sum = (first + second) % MOD;
    lli ans = ((i-1)*sum) % MOD;
    dp[i] = ans;
  }
  return dp[n];
}


// SPACE OPTIMIZATION
lli solveSpace(int n) {
  lli prev2 = 0;
  lli prev1 = 1;
  for(int i=3; i<=n; i++) {
    lli first = prev1 % MOD;
    lli second = prev2 % MOD;
    lli sum = (first + second) % MOD;
    lli ans = ((i-1)*sum) % MOD;
    prev2 = prev1;
    prev1 = ans;
  }
  return prev1;
}