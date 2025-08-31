#include <vector>
#include <algorithm>
#include <map>
using namespace std;

class Solution {
public:
	int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
		int n = startTime.size();
		// Step 1: Bundle jobs as (end, start, profit)
		vector<tuple<int, int, int>> jobs;
		for (int i = 0; i < n; ++i) {
			jobs.emplace_back(endTime[i], startTime[i], profit[i]);
		}

		// Step 2: Sort jobs by end time
		sort(jobs.begin(), jobs.end());

		// Step 3: DP table
		// dp = [ {end, max_profit} ...]
		vector<pair<int, int>> dp = { {0, 0} }; // (endTime, profit)

		for (auto& [end, start, p] : jobs) {
			// Find the last job in dp with endTime <= start
			auto it = upper_bound(dp.begin(), dp.end(), make_pair(start, INT_MAX));
			--it;
			int currProfit = it->second + p;
			// Only add if this increases profit
			if (currProfit > dp.back().second) {
				dp.emplace_back(end, currProfit);
			}
		}

		return dp.back().second;
	}
};


class Solution {
public:
	int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
		int n = profit.size();
		vector<tuple<int, int, int>> jobs(n);
		for (int i = 0; i < n; ++i)
			jobs[i] = { endTime[i], startTime[i], profit[i] };
		sort(jobs.begin(), jobs.end());

		vector<int> dp(n + 1, 0);

		for (int i = 0; i < n; ++i) {
			auto [e, s, p] = jobs[i];
			int j = upper_bound(jobs.begin(), jobs.begin() + i, s,
				[](int value, const tuple<int, int, int>& job) {
					return value < get<0>(job);
				}) - jobs.begin();
			dp[i + 1] = max(dp[i], dp[j] + p);
		}
		return dp[n];
	}
};



class Solution {
public:
	int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
		int n = startTime.size();
		vector<vector<int>> jobs(n);
		for (int i = 0; i < n; ++i)
			jobs[i] = { endTime[i], startTime[i], profit[i] };
		sort(jobs.begin(), jobs.end());

		map<int, int> dp; // endTime -> max profit so far
		dp[0] = 0; // No job, zero profit

		for (auto& job : jobs) {
			int e = job[0], s = job[1], p = job[2];
			// Find the profit before this job starts
			auto it = dp.upper_bound(s);
			--it;
			int cur = it->second + p;
			// Only update if this job increases profit
			if (cur > dp.rbegin()->second)
				dp[e] = cur;
		}
		return dp.rbegin()->second;
	}
};



struct Job {
	int start, end, profit;
};

int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
	int n = startTime.size();
	vector<Job> jobs(n);
	for (int i = 0; i < n; i++) {
		jobs[i] = { startTime[i], endTime[i], profit[i] };
	}
	sort(jobs.begin(), jobs.end(), [](Job& a, Job& b) {
		return a.end < b.end;
		});

	vector<int> dp(n);
	dp[0] = jobs[0].profit;

	for (int i = 1; i < n; i++) {
		int inclProfit = jobs[i].profit;

		int low = 0, high = i - 1, last = -1;
		while (low <= high) {
			int mid = (low + high) / 2;
			if (jobs[mid].end <= jobs[i].start) {
				last = mid;
				low = mid + 1;
			}
			else {
				high = mid - 1;
			}
		}
		if (last != -1) {
			inclProfit += dp[last];
		}
		dp[i] = max(dp[i - 1], inclProfit);
	}
	return dp[n - 1];
}
