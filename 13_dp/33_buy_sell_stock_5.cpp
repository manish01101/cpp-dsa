#include<bits/stdc++.h>
using namespace std;

/*
-> pay transaction fee for each complete transaction
-> similar as buy_sell_stock_2

if(canBuy)
	profit = max[
		buy => -prices[i] + f(i+1, false)
		skip => 0+f(i+1, true)
	]
else
	proft = max[
		buy => +prices[i] - fees + f(i+1, true)
		skip => 0+f(i+1, false)
	]
*/


int solveSpaceOpt(vector<int>& prices, int fee) {
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
				profit = max((prices[index] - fee + next[true]), (0 + next[false]));
			}
			curr[canBuy] = profit;
		}
		next = curr;
	}
	return next[true];
}

int maxProfit(vector<int>& prices, int fee) {
	return solveSpaceOpt(prices, fee);
}