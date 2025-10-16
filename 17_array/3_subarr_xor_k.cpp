/*
Problem Statement: Given an array of integers A and an integer B. Find the total number of subarrays having bitwise XOR of all elements equal to k.
*/
#include<bits/stdc++.h>
using namespace std;
int solve(vector<int>& arr, int k) {
	int n = arr.size();
	int cnt = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = i; j < n; ++j) {
			int xorr = 0;
			for (int p = i; p <= j; ++p) {
				xorr ^= arr[p];
			}
			if (xorr == k)
				cnt++;
		}
	}
	return cnt;
}
int solveOpt(vector<int>& arr, int k) {
	int n = arr.size();
	int cnt = 0;
	for (int i = 0; i < n; ++i) {
		int xorr = 0;
		for (int j = i; j < n; ++j) {
			xorr ^= arr[j];
			if (xorr == k)
				cnt++;
		}
	}
	return cnt;
}
int subarraysWithXorK(vector<int> a, int k) {
	int n = a.size(); //size of the given array.
	int xr = 0;
	map<int, int> mpp; //declaring the map.
	mpp[xr]++; //setting the value of 0.
	int cnt = 0;

	for (int i = 0; i < n; i++) {
		// prefix XOR till index i:
		xr = xr ^ a[i];

		//By formula: x = xr^k:
		int x = xr ^ k;

		// add the occurrence of xr^k
		// to the count:
		cnt += mpp[x];

		// Insert the prefix xor till index i
		// into the map:
		mpp[xr]++;
	}
	return cnt;
}
int subarraysWithXorK2(vector<int>& arr, int k) {
	int n = arr.size();
	int count = 0;
	vector<int> prefix(n);
	prefix[0] = arr[0];
	for (int i = 1; i < n; ++i) {
		prefix[i] = prefix[i - 1] ^ arr[i];
	}

	unordered_map<int, int> mp;
	for (int j = 0; j < n; ++j) {
		if (prefix[j] == k) count++;

		int val = prefix[j] ^ k;
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
int main() {
	vector<int> a = { 4, 2, 2, 6, 4 };
	int k = 6;
	int ans = subarraysWithXorK2(a, k);
	cout << "The number of subarrays with XOR k is: "
		<< ans << "\n";
	return 0;
}