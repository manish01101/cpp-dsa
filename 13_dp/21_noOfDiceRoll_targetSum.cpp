#include<bits/stdc++.h>
using namespace std;
class Solution {
    const int MOD = 1e9 + 7;
	int solveRec(int n, int k, int target) {
		if (n == 0) {
			return target == 0 ? 1 : 0;
		}
		if (target < 0) {
			return 0;
		}
		int ans = 0;
		for (int face = 1; face <= k; face++) {
			ans = (ans + solveRec(n - 1, k, target - face)) % MOD;
		}
		return ans;
	}
    int solveMem(int n, int k, int target, vector<vector<int>> &dp) {
        if(n==0) return target==0 ? 1 : 0;
        if(target < 0) return 0;

        if(dp[n][target] != -1) return dp[n][target];

        int ans = 0;
        for(int face = 1; face<=k; face++) {
            if (target - face >= 0) 
               ans = (ans + solveMem(n - 1, k, target - face, dp)) % MOD;
        } 
        return dp[n][target] = ans;
    }
    int solveTab(int n, int k, int target) {
        vector<vector<int>> dp(n+1, vector<int>(target+1, 0));
        /* 
        in memoization: n to 0 & target to 0
        in tabulation : 0 to n & 0 to target
        */
        // base case
        dp[0][0] = 1;

        for(int i=1; i<=n; i++) {
            for(int j=1; j<=target; j++) {
                int ans = 0;
                for(int face=1; face<=k; face++) {
                    if( j-face >= 0) {
                        ans = (ans + dp[i-1][j-face]) % MOD;
                    }
                }
                dp[i][j] = ans;
            }
        }
        return dp[n][target];
    }
    int solveSpcOpt(int n, int k, int target) {
        vector<int> prev(target+1, 0);
        vector<int> curr(target+1, 0);
        // base case
        prev[0] = 1;

        for(int i=1; i<=n; i++) {
            for(int j=1; j<=target; j++) {
                int ans = 0;
                for(int face=1; face<=k; face++) {
                    if(j-face >= 0) {
                        ans = (ans + prev[j-face]) % MOD;
                    }
                }
                curr[j] = ans;
            }
            prev = curr;
        }
        return prev[target];
    }
public:
	int numRollsToTarget(int n, int k, int target) {
		// recursion
		// return solveRec(n, k, target);

        // rec + mem -> top-down dp
        // vector<vector<int>> dp(n+1, vector<int>(target+1, -1));
        // return solveMem(n, k, target, dp);

        // tabulaton -> bottom-up dp
        // return solveTab(n, k, target);

        // space opt
        return solveSpcOpt(n, k, target);
	}
};

long long solve(int dice, int faces, int target) {
	// base case
	if (target < 0)
		return 0;
	if (dice == 0 && target != 0)
		return 0;
	if (target == 0 && dice != 0)
		return 0;
	if (dice == 0 && target == 0)
		return 1;

	long long ans = 0;
	for (int i = 1; i <= faces; i++) {
		ans = ans + solve(dice - 1, faces, target - i);
	}
	return ans;
}

/* dice: n to 0 & target: x to 0 */
long long solveMem(int dice, int faces, int target, vector<vector<long long>>& dp) {
	// base case
	if (target < 0)
		return 0;
	if (dice == 0 && target != 0)
		return 0;
	if (target == 0 && dice != 0)
		return 0;
	if (dice == 0 && target == 0)
		return 1;

	if (dp[dice][target] != -1)
		return dp[dice][target];

	long long ans = 0;
	for (int i = 1; i <= faces; i++) {
		ans = ans + solveMem(dice - 1, faces, target - i);
	}
	return dp[dice][target] = ans;
}

/* dice: 0 to n  & target: 0 to x  */
long long solveTab(int d int f, int t) {
	vector<vector<long long>> dp(d + 1, vector<long long>(t + 1, 0));
	dp[0][0] = 1;

	for (int dice = 1; dice <= d; dice++) {
		for (int target = 1; target <= t; target++) {
			long long ans = 0;
			for (int i = 1; i <= f; i++) {
				if (target - i >= 0)
					ans = ans + dp[dice - 1][target - i];
			}
			dp[dice][target] = ans;
		}
	}
	return dp[d][t];
}

long long solveSpaceOpt(int d int f, int t) {
	vector<long long > prev(t + 1, 0);
	vector<long long > curr(t + 1, 0);
	prev[0] = 1;

	for (int dice = 1; dice <= d; dice++) {
		for (int target = 1; target <= t; target++) {
			long long ans = 0;
			for (int i = 1; i <= f; i++) {
				if (target - i >= 0)
					ans = ans + prev[target - i];
			}
			curr[target] = ans;
		}
		prev = curr;
	}
	return prev[t];
}
long long noOfWays(int M, int N, int X) {
	/* -- recursion --*/
	// return solve(N, M, X);

	/* --- rec + mem --- */
	// vector<vector<long long>> dp(N + 1, vector<long long>(X + 1, -1));
	// return solveMem(N, M, X, dp);

	/* --- tabulation --- */
	// return solveTab(N, M, X);

	/* -- space opt --- */
	return solveSpaceOpt(N, M, X);

}