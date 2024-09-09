#include<bits/stdc++.h>
using namespace std;

/*
cuboid (l, b, h)
sort all dimension for every cuboid, so last index ele is max, that will be height
again sort cuboid on the basis of l & b, last cuboid will be bigger
use longest increasing subseq. logic
*/
bool check(vector<int>& base, vector<int>& newBox) {
	if (newBox[0] <= base[0] && newBox[1] <= base[1] && newBox[2] <= base[2]) {
		return true;
	}
	else
		return false;
}
int solveSpaceOpt(int n, vector<vector<int>>& a) {
	vector<int> currRow(n + 1, 0);
	vector<int> nextRow(n + 1, 0);
	for (int curr = n - 1; curr >= 0; curr--) {
		for (int prev = curr - 1; prev >= -1; prev--) {
			// include
			int take = 0;
			if (prev == -1 || check(a[curr], a[prev])) {
				take = a[curr][2] + nextRow[curr + 1];
			}
			// exclude
			int notTake = 0 + nextRow[prev + 1];
			currRow[prev + 1] = max(take, notTake);
		}
		nextRow = currRow;
	}
	return nextRow[0];
}
int maxHeight(vector<vector<int>>& cuboids) {
	// step 1
	for (auto& cuboid : cuboids) {
		sort(cuboid.begin(), cuboid.end());
	}
	// step 2
	sort(cuboids.begin(), cuboids.end());
	return solveSpaceOpt(cuboids.size(), cuboids);
}