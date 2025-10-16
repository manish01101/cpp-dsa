vector<vector<int>> twoSum(vector<int>& nums, int target) {
	int n = nums.size();
	vector<vector<int>> ans;
	int i = 0;
	int j = n - 1;
	while (i < j) {
		int sum = nums[i] + nums[j];
		if (sum == target) {
			ans.push_back({ nums[i], nums[j] });
			// skip duplicates ele for i and j
			while (i < j and nums[i] == nums[i + 1]) i++;
			while (i < j and nums[j] == nums[j - 1]) j--;
			i++;
			j--;
		}
		else if (sum < target) {
			i++;
		}
		else {
			j--;
		}
	}
	return ans;
}
vector<vector<int>> threeSum(vector<int>& nums) {
	vector<vector<int>> ans;
	sort(nums.begin(), nums.end());
	int n = nums.size();
	for (int i = 0; i < n - 2; ++i) {
		if (i > 0 and nums[i] == nums[i - 1]) continue;
		int j = i + 1;
		int k = n - 1;
		while (j < k) {
			int sum = nums[i] + nums[j] + nums[k];
			if (sum == 0) {
				ans.push_back({ nums[i], nums[j], nums[k] });
				// skip duplicates ele for j and k
				while (j < k and nums[j] == nums[j + 1]) j++;
				while (j < k and nums[k] == nums[k - 1]) k--;
				j++;
				k--;
			}
			else if (sum < 0) {
				j++;
			}
			else {
				k--;
			}
		}
	}
	return ans;
}
vector<vector<int>> fourSum(vector<int>& nums, int target) {
	vector<vector<int>> ans;
	sort(nums.begin(), nums.end());
	int n = nums.size();
	for (int i = 0; i < n; ++i) {
		// duplicate
		if (i > 0 and nums[i] == nums[i - 1]) continue;
		for (int j = i + 1; j < n; ++j) {
			// duplicate
			if (j > i + 1 and nums[j] == nums[j - 1]) continue;
			int p = j + 1;
			int q = n - 1;
			while (p < q) {
				long long sum = (long long)nums[i] + nums[j] + nums[p] + nums[q];

				if (sum == target) {
					ans.push_back({ nums[i], nums[j], nums[p], nums[q] });
					// duplicate
					while (p < q and nums[p] == nums[p + 1]) p++;
					while (p < q and nums[q] == nums[q - 1]) q--;
					p++;
					q--;
				}
				else if (sum < target) {
					p++;
				}
				else {
					q--;
				}
			}
		}
	}
	return ans;
}