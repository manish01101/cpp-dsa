#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <vector>

using namespace std;

#define endl '\n'

using pii = pair<int, int>;
using ll = long long;

void merge(int s, int e, vector<int>& arr, int& count) {
	int i = s;
	int mid = (s + e) / 2;
	int j = mid + 1;
	vector<int> temp;
	while (i <= mid and j <= e) {
		if (arr[i] <= arr[j]) {
			temp.push_back(arr[i++]);
		}
		else {
			temp.push_back(arr[j++]);
			count += (mid - i + 1);
		}
	}
	while (i <= mid) {
		temp.push_back(arr[i++]);
	}
	while (j <= e) {
		temp.push_back(arr[j++]);
	}
	for (int i = s; i <= e; ++i) {
		arr[i] = temp[i - s];
	}
}
void mergeSort(int s, int e, vector<int>& arr, int& count) {
	if (s < e) {
		int mid = (s + e) / 2;
		mergeSort(s, mid, arr, count);
		mergeSort(mid + 1, e, arr, count);
		merge(s, e, arr, count);
	}
}

int main() {
	vector<int> arr = { 1, 3, 5, 10, 2, 6, 8, 9 };
	int count = 0;
	mergeSort(0, arr.size() - 1, arr, count);
	for (auto e : arr) {
		cout << e << " ";
	}cout << endl;
	cout << count << endl;
	return 0;
}