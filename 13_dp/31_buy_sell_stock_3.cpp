#include<bits/stdc++.h>
using namespace std;

/* can do atmost 2 transaction (1 transaction includes buy and sell)

f(index, canBuy, limit) ; limit = 2

base case
=> if index == n return 0
=> if limit == 0 return 0;

if(canBuy)
	profit = max[
		buy => -prices[i] + f(index+1, false, limit)
		skip => 0 + f(index+1, true, limit)
	]
else
	profit = max[
		sell => +prices[i] + f(index+1, true, limit--)
		skip => 0 + f(index+1, false, limit)
	]
*/

int solve(int index, bool canBuy, int limit, vector<int>& prices) {
	if (index == prices.size())
		return 0;
	if (limit == 0)
		return 0;

	int profit = 0;
	if (canBuy) {
		profit = max((-prices[index] + solve(index + 1, false, limit, prices)), (0 + solve(index + 1, true, limit, prices)));
	}
	else {
		profit = max((prices[index] + solve(index + 1, true, limit--, prices)), (0 + solve(index + 1, false, limit, prices)));
	}
	return profit;
}

int solveMem(int index, bool canBuy, int limit, vector<int>& prices, vector<vector<vector<int>>>& dp) {
	if (index == prices.size())
		return 0;
	if (limit == 0)
		return 0;

	if (dp[index][canBuy][limit] != -1) {
		return dp[index][canBuy][limit];
	}

	int profit = 0;
	if (canBuy) {
		profit = max((-prices[index] + solveMem(index + 1, false, limit, prices, dp)), (0 + solveMem(index + 1, true, limit, prices, dp)));
	}
	else {
		profit = max((prices[index] + solveMem(index + 1, true, limit - 1, prices, dp)), (0 + solveMem(index + 1, false, limit, prices, dp)));
	}
	return dp[index][canBuy][limit] = profit;
}

int solveTab(vector<int>& prices) {
	int n = prices.size();
	vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(3, 0)));

	for (int index = n - 1; index >= 0; index--) {
		for (int canBuy = 0; canBuy <= 1; canBuy++) {
			for (int limit = 1; limit <= 2; limit++) {
				int profit = 0;
				if (canBuy) {
					profit = max((-prices[index] + dp[index + 1][false][limit]), (0 + dp[index + 1][true][limit]));
				}
				else {
					profit = max((prices[index] + dp[index + 1][true][limit - 1]), (0 + dp[index + 1][false][limit]));
				}
				dp[index][canBuy][limit] = profit;
			}
		}
	}
	return dp[0][true][2];
}

int solveSpaceOpt(vector<int>& prices) {
	int n = prices.size();
	vector<vector<int>> curr(2, vector<int>(3, 0));
	vector<vector<int>> next(2, vector<int>(3, 0));

	for (int index = n - 1; index >= 0; index--) {
		for (int canBuy = 0; canBuy <= 1; canBuy++) {
			for (int limit = 1; limit <= 2; limit++) {
				int profit = 0;
				if (canBuy) {
					profit = max((-prices[index] + next[false][limit]), (0 + next[true][limit]));
				}
				else {
					profit = max((prices[index] + next[true][limit - 1]), (0 + next[false][limit]));
				}
				curr[canBuy][limit] = profit;
			}
		}
		next = curr;
	}
	return next[true][2];
}
int maxProfit(vector<int>& prices) {
	int n = prices.size();
	/* -- recursion -- */
	// return solve(0, true, 2, prices);

	/* -- rec + mem -- */
	// vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(3, -1)));
	// return solveMem(0, true, 2, prices, dp);

	/* --- tabulation --- */
	// return solveTab(prices); 

	/* -- space opt -- */
	return solveSpaceOpt(prices);
}