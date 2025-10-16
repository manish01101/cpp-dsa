#include<bits/stdc++.h>
using namespce std;

int solve(vector<int>& arr, int k) {
	int ans = 0;
	for (int i = 0; i < arr.size(); ++i) {
		int sum = 0;
		for (int j = i; j < arr.size(); ++j) {
			sum += arr[j];
			if (sum == k)
				ans++;
		}
	}
	return ans;
}
/*
optimal
arr =    9  4 20  3 10  5; 		k = 33
prefix = 9 13 33 36 46 51
			   i	 j
k = pre[j] - pre[i-1]
case 1:
=> pre[i-1] = pre[j] - k => 46-33 = 13 present at 1
-> i-1 = 1 => i = 2 so subarr range = [i..j]

case 2: pre[j] == k -> ans++
*/
int subarraySum(vector<int>& arr, int k) {
	int n = arr.size();
	int count = 0;
	vector<int> prefix(n);
	prefix[0] = arr[0];
	for (int i = 1; i < n; ++i) {
		prefix[i] = prefix[i - 1] + arr[i];
	}

	unordered_map<int, int> mp;
	for (int j = 0; j < n; ++j) {
		if (prefix[j] == k) count++;

		int val = prefix[j] - k;
		if (mp.find(val) != mp.end()) {
			count += mp[val];
		}
		if (mp.find(prefix[j]) == mp.end()) {
			mp[prefix[j]] = 0;
		}
		mp[prefix[j]]++;
	}
	return count;
}