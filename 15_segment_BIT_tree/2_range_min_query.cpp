#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <vector>

using namespace std;

#define endl '\n'



void buildSegTree(vector<int>& arr, int s, int e, int segTreeIdx, vector<int>& segTree) {
	if (s == e) {
		segTree[segTreeIdx] = arr[s];
		return;
	}
	int mid = s + (e - s) / 2;
	buildSegTree(arr, s, mid, 2 * segTreeIdx + 1, segTree);
	buildSegTree(arr, mid + 1, e, 2 * segTreeIdx + 2, segTree);
	// finding min
	segTree[segTreeIdx] = min(segTree[2 * segTreeIdx + 1], segTree[2 * segTreeIdx + 2]);
}
int getMin(int segTreeIdx, int s, int e, int l, int r, vector<int>& segTree) {
	// non-overlapping
	if (r < s || l > e)
		return INT_MAX;
	// complete overlapping
	else if (l <= s and r >= e)
		return segTree[segTreeIdx];
	// partial overlapping
	else {
		int mid = s + (e - s) / 2;
		int leftMin = getMin(2 * segTreeIdx + 1, s, mid, l, r, segTree);
		int rightMin = getMin(2 * segTreeIdx + 2, mid + 1, e, l, r, segTree);
		return min(leftMin, rightMin);
	}
}
int main() {
	vector<int> arr = { 1, 3, 2, 7, 9, 11 };
	vector<int> segTree(4 * arr.size());
	int segTreeIdx = 0, s = 0, e = arr.size() - 1;
	buildSegTree(arr, s, e, segTreeIdx, segTree);

	int q; cout << "enter no. of query: "; cin >> q;
	while (q--) {
		int l, r; cout << "enter l and r: ";
		cin >> l >> r;
		if (l > r) {
			cout << "enter valid range" << endl;
			continue;
		}

		int ans = getMin(0, 0, arr.size() - 1, l, r, segTree);
		cout << "min is: " << ans << endl;
	}
	return 0;
}