#include <bits/stdc++.h>
using namespace std;

bool searchMatrix(vector<vector<int>>& matrix, int target) {
	if (matrix.empty() || matrix[0].empty()) return false;

	int m = matrix.size(), n = matrix[0].size();
	int left = 0, right = m * n - 1;

	while (left <= right) {
		int mid = left + (right - left) / 2;
		int val = matrix[mid / n][mid % n];

		if (val == target) return true;
		else if (val < target) left = mid + 1;
		else right = mid - 1;
	}

	return false;
}

int main() {
	vector<vector<int>> matrix = {
		{1, 3, 5, 7},
		{10, 11, 16, 20},
		{23, 30, 34, 50}
	};

	cout << boolalpha;
	cout << searchMatrix(matrix, 3) << endl;   // true
	cout << searchMatrix(matrix, 13) << endl;  // false
}
