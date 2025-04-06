class Solution {
	bool solveRec(vector<int>& nums, int index, int target) {
		if (index >= nums.size() or target < 0) return false;
		if (target == 0) return true;

		int incl = solveRec(nums, index + 1, target - nums[index]);
		int excl = solveRec(nums, index + 1, target);
		return incl or excl;
	}
	bool solveMem(vector<int>& nums, int index, int target, vector<vector<int>>& dp) {
		if (index >= nums.size() or target < 0) return false;
		if (target == 0) return true;

		if (dp[index][target] != -1) return dp[index][target];

		bool incl = solveMem(nums, index + 1, target - nums[index], dp);
		bool excl = solveMem(nums, index + 1, target, dp);

		return dp[index][target] = (incl or excl);
	}
	bool solveTab(vector<int>& nums, int t) {
		int n = nums.size();
		vector<vector<bool>> dp(n + 1, vector<bool>(t + 1, false));

		// base case
		for (int i = 0; i <= n; i++) dp[i][0] = true;

		for (int index = n - 1; index >= 0; index--) {
			for (int target = 0; target <= t; target++) {
				bool incl = false;
				if (target - nums[index] >= 0) {
					incl = dp[index + 1][target - nums[index]];
				}
				bool excl = dp[index + 1][target];

				dp[index][target] = (incl or excl);
			}
		}
		return dp[0][t];
	}
	bool solveSpcOpt(vector<int>& nums, int t) {
		int n = nums.size();
		vector<bool> curr(t + 1, false);
		vector<bool> next(t + 1, false);

		curr[0] = true;
		next[0] = true;

		for (int index = n - 1; index >= 0; index--) {
			for (int target = 0; target <= t; target++) {
				bool incl = false;
				if (target - nums[index] >= 0) {
					incl = next[target - nums[index]];
				}
				bool excl = next[target];

				curr[target] = (incl or excl);
			}
			next = curr;
		}
		return next[t];
	}
public:
	bool canPartition(vector<int>& nums) {
		int sum = 0;
		for (auto& num : nums) {
			sum += num;
		}
		if (sum & 1) return false;

		int startIdx = 0;
		// recursion 
		// return solveRec(nums, startIdx, sum/2);

		// rec + mem -> top-down dp
		// vector<vector<int>> dp(nums.size()+1, vector<int>(sum/2+1, -1));
		// return solveMem(nums, startIdx, sum/2, dp);

		// tabulation -> bottom-up dp
		// return solveTab(nums, sum/2);

		// space opt
		return solveSpcOpt(nums, sum / 2);
	}
};