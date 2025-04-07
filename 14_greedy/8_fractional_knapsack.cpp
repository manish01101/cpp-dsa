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
	vector<pair<double, Item>> unitValue;
	for (int i = 0; i < n; i++) {
		double perUnitValue = (1.0 * arr[i].value) / arr[i].weight;
		unitValue.push_back({ perUnitValue, arr[i] });
	}

	sort(unitValue.begin(), unitValue.end(), [](pair<double, Item>& a, pair<double, Item>& b) {
		return a.first > b.first;
		});

	double totalValue = 0;
	for (int i = 0; i < n; i++) {
		if (unitValue[i].second.weight > W) { // item weight is more than capacity
			// take fraction of item
			totalValue += W * unitValue[i].first;
			W = 0;
		}
		else { // item wt is <= capacity
			totalValue += unitValue[i].second.value;
			W -= unitValue[i].second.weight;
		}
	}
	return totalValue;
}