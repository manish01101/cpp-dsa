#include<bits/stdc++.h>
using namespace std;

/* same as prev ques, but handle first and last index as they are neighbour */
long long int solve(vector<int>& val) {
	int n = val.size();
	long long int prev2 = 0;
	long long int prev1 = val[0];

	for (int i = 1; i < n; i++) {
		long long int incl = prev2 + val[i];
		long long int excl = prev1 + 0;

		long long int curr = max(incl, excl);
		prev2 = prev1;
		prev1 = curr;
	}
	return prev1;
}
long long int houseRobber(vector<int>& valueInHouse) {
	int n = valueInHouse.size();
	if (n == 1)
		return valueInHouse[0];

	vector<int> first, second;
	for (int i = 0; i < n; i++) {
		if (i != n - 1)
			first.push_back(valueInHouse[i]);
		if (i != 0)
			second.push_back(valueInHouse[i]);
	}
	return max(solve(first), solve(second));
}