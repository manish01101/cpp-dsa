#include<bits/stdc++.h>
using namespace std;

/* here multiple buy and sell, if but then first sell and so on

canBuy = true -> buy it
			  -> ignore
canBuy = false -> sell it
				-> ignore it
buy => profit + (-prices)
sell => profit + (+prices)


if(canBuy)
	profit = max[
		buy => -prices[i] + f(i+1, false)
		skip => 0+f(i+1, true)
	]
else
	proft = max[
		buy => +prices[i] + f(i+1, true)
		skip => 0+f(i+1, false)
	]
 */

int solve(int index, bool canBuy, vector<int>& prices) {
	if (index == prices.size())
		return 0;

	int profit = 0;
	if (canBuy) {
		profit = max((-prices[index] + solve(index + 1, false, prices)), (0 + solve(index + 1, true, prices)));
	}
	else {
		profit = max((prices[index] + solve(index + 1, true, prices)), (0 + solve(index + 1, false, prices)));
	}
	return profit;
}

int solveMem(int index, bool canBuy, vector<int>& prices, vector<vector<int>>& dp) {
	if (index == prices.size())
		return 0;

	if (dp[index][canBuy] != -1) {
		return dp[index][canBuy];
	}

	int profit = 0;
	if (canBuy) {
		profit = max((-prices[index] + solveMem(index + 1, false, prices, dp)), (0 + solveMem(index + 1, true, prices, dp)));
	}
	else {
		profit = max((prices[index] + solveMem(index + 1, true, prices, dp)), 0 + solveMem(index + 1, false, prices, dp));
	}
	return dp[index][canBuy] = profit;
}

int solveTab(vector<int>& prices) {
	int n = prices.size();
	vector<vector<int>> dp(n + 1, vector<int>(2, 0));

	for (int index = n - 1; index >= 0; index--) {
		for (int canBuy = 0; canBuy <= 1; canBuy++) {
			int profit = 0;
			if (canBuy) {
				profit = max((-prices[index] + dp[index + 1][false]), (0 + dp[index + 1][true]));
			}
			else {
				profit = max((prices[index] + dp[index + 1][true]), (0 + dp[index + 1][false]));
			}
			dp[index][canBuy] = profit;
		}
	}
	return dp[0][true];
}

int solveSpaceOpt(vector<int>& prices) {
	int n = prices.size();
	vector<int> curr(2, 0);
	vector<int> next(2, 0);

	for (int index = n - 1; index >= 0; index--) {
		for (int canBuy = 0; canBuy <= 1; canBuy++) {
			int profit = 0;
			if (canBuy) {
				profit = max((-prices[index] + next[false]), (0 + next[true]));
			}
			else {
				profit = max((prices[index] + next[true]), (0 + next[false]));
			}
			curr[canBuy] = profit;
		}
		next = curr;
	}
	return next[true];
}


int maxProfit(vector<int>& prices) {
	int n = prices.size();
	/* -- recursion -- */
	// return solve(0, true, prices);

	/* -- rec + mem -- */
	// vector<vector<int>> dp(n, vector<int>(2, -1));
	// return solveMem(0, true, prices, dp);

	/* -- tabulation -> bottom up -- */
	// return solveTab(prices);

	/* -- space opt -- */
	return solveSpaceOpt(prices);
}