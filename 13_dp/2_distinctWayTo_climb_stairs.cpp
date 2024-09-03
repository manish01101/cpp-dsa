#include<iostream>

using namespace std;

#define MOD 1000000007

int solve(long long nStairs, int start) {
	// base case
	if (start == nStairs) {
		return 1;
	}
	if (start > nStairs) {
		return 0;
	}
	return (solve(nStairs, start + 1) + solve(nStairs, start + 2)) % MOD;
}
int countDistinctWayToClimbStair(long long nStairs) {
	int ans = solve(nStairs, 0);
	return ans;
}