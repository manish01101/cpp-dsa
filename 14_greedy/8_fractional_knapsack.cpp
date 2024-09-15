#include<bits/stdc++.h>
using namespace std;

/*
find per unit val i.e. (val/wt);
sort by per unit val
use greedy
*/
struct Item {
	int value;
	int weight;
};
double fractionalKnapsack(int W, Item arr[], int n) {
	vector<pair<double, Item>> v;
	for (int i = 0; i < n; i++) {
		double perUnitValue = (1.0 * arr[i].value) / arr[i].weight;
		v.push_back({ perUnitValue, arr[i] });
	}

	sort(v.begin(), v.end(), [](pair<double, Item>& a, pair<double, Item>& b) {
		return a.first > b.first;
		});

	double totalValue = 0;
	for (int i = 0; i < n; i++) {
		if (v[i].second.weight > W) {
			// take fraction of item
			totalValue += W * v[i].first;
			W = 0;
		}
		else {
			totalValue += v[i].second.value;
			W -= v[i].second.weight;
		}
	}
	return totalValue;
}