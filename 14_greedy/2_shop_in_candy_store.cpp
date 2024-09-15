#include<bits/stdc++.h>
using namespace std;

/*
find min and max amount of money to buy all candy
buy one get two free

for min amount
=> buy least costly candy and in free get most costly candy

for max amount
=> buy most costly candy and in free get least costly candy
*/

vector<int> candyStore(int candies[], int N, int K) {
	sort(candies, candies + N);

	int minAmount = 0;
	int buyIndex = 0;
	int freeIndex = N - 1;

	while (buyIndex <= freeIndex) {
		minAmount += candies[buyIndex++];
		freeIndex -= K;
	}

	int maxAmount = 0;
	buyIndex = N - 1;
	freeIndex = 0;
	while (buyIndex >= freeIndex) {
		maxAmount += candies[buyIndex--];
		freeIndex += K;
	}
	vector<int> ans;
	ans.push_back(minAmount);
	ans.push_back(maxAmount);
	return ans;
}