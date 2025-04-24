#include <iostream>
using namespace std;
/*
SEGMENT TREE : used for range query
why segment tree?
brute force : query => O(n) & update => O(1)
prefix sum : query => O(1) & update => O(n)
segment tree: query => O(log n) & update => O(log n)

Total leaves(x) = log n (base 2)
Total nodes = 2^x - 1 => 2*n -1
but we take 4*n for safety reason; (segment tree-> full binary tree)


QUERY ON SEGMENT TREE: (3 case)
case 1: non overlap
	qj <= si  => qi---------qj
							si--------sj
	or
	qi >= sj  => si---------sj
							qi--------qj
return 0;


case 2: complete overlap
	(si >= qi && sj <= qj) =>  qi--------------qj
								si--------sj
return tree[i];


case 3: partial overlap
	qi---------qj
			si--------sj
	or
			qi--------qj
	si---------sj

	step 1: find mid index
	step 2 : return sum of subquery
*/

// BUILD
void buildST(vector<int>& arr, int stIdx, int start, int end, vector<int>& segmentTree) { // O(n)-> once
	if (start == end) { // leaf node
		segmentTree[stIdx] = arr[start];
		return;
	}

	int mid = (start + end) / 2;
	buildST(arr, 2 * stIdx + 1, start, mid, segmentTree);
	buildST(arr, 2 * stIdx + 2, mid + 1, end, segmentTree);
	segmentTree[stIdx] = segmentTree[2 * stIdx + 1] + segmentTree[2 * stIdx + 2];
}

// QUERY SUM
int getSumUtil(int i, int si, int sj, int qi, int qj, vector<int>& segmentTree) { // O(log n)
	if (qj <= si || qi >= sj) { // non overlapping
		return 0;
	}
	else if (si >= qi && sj <= qj) { // complete overlapping
		return segmentTree[i];
	}
	else { // partial overlapping
		int mid = (si + sj) / 2;
		int left = getSumUtil(2 * i + 1, si, mid, qi, qj, segmentTree);
		int right = getSumUtil(2 * i + 2, mid + 1, sj, qi, qj, segmentTree);
		return left + right;
	}
}
int getSum(vector<int>& arr, int qi, int qj, vector<int>& segmentTree) {
	int i = 0, si = 0, sj = arr.size() - 1;
	return getSumUtil(i, si, sj, qi, qj, segmentTree);
}

// QUERY UPDATE
void updateSTUtil(int i, int si, int sj, int idx, int diff, vector<int>& segmentTree) { // O(log n)
	if (idx < si || idx > sj) { // non-overlapping
		return;
	}
	// idx lie in range
	segmentTree[i] += diff;
	// check currPos is not leaf node -> if so update its child val
	if (si != sj) { // non-leaf node
		int mid = (si + sj) / 2;
		updateSTUtil(2 * i + 1, si, mid, idx, diff, segmentTree);
		updateSTUtil(2 * i + 2, mid + 1, sj, idx, diff, segmentTree);
	}
}
void updateST(vector<int>& arr, int idx, int newVal, vector<int>& segmentTree) {
	int diff = newVal - arr[idx];
	arr[idx] = newVal;
	int i = 0, si = 0, sj = arr.size() - 1;
	updateSTUtil(i, si, sj, idx, diff, segmentTree);
}


int main() {
	vector<int> arr = { 1, 2, 3, 4, 5, 6, 7, 8 };
	int n = arr.size();

	// BUILDING SEGMENT TREE
	vector<int> segmentTree(4 * n);
	int stidx = 0, start = 0, end = n - 1;
	buildST(arr, stidx, start, end, segmentTree);

	for (auto ele : segmentTree) {
		cout << ele << " ";
	} cout << endl;

	// QUERY ON SEGMENT TREE: sum of numbers in a range
	int qi = 2;
	int qj = 5;
	cout << getSum(arr, qi, qj, segmentTree) << endl;


	// UPDATE OPERATION ON SEGMENT TREE
	int idx = 2;
	int newVal = 9;
	updateST(arr, idx, newVal, segmentTree);

	for (auto ele : segmentTree) {
		cout << ele << " ";
	} cout << endl;

	cout << getSum(arr, qi, qj, segmentTree) << endl;
}