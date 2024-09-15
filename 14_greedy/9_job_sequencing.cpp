#include<bits/stdc++.h>
using namespace std;

/*
given : jobid, deadline, profit
-> sort by profit
-> try to complete job at last, deadline
*/

struct Job {
	int id;
	int deadline;
	int profit;
};
vector<int> JobScheduling(Job arr[], int n) {
	// sort by profit
	sort(arr, arr + n, [](Job a, Job b) {
		return a.profit > b.profit;
		});

	// create schedule arr
	int maxiDeadline = INT_MIN;
	for (int i = 0; i < n; i++) {
		if (arr[i].deadline > maxiDeadline)
			maxiDeadline = arr[i].deadline;
	}
	vector<int> schedule(maxiDeadline + 1, -1);

	// process
	int count = 0;
	int maxProfit = 0;
	for (int i = 0; i < n; i++) {
		int currProfit = arr[i].profit;
		int currJobID = arr[i].id;
		int currDeadline = arr[i].deadline;
		// trying to do at deadline
		for (int k = currDeadline; k > 0; k--) {
			if (schedule[k] == -1) {
				schedule[k] = currJobID;
				maxProfit += currProfit;
				count++;
				break;
			}
		}
	}
	vector<int> ans;
	ans.push_back(count);
	ans.push_back(maxProfit);
	return ans;
}
