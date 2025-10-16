class Solution {
public:
	vector<int> maxSlidingWindow(vector<int>& nums, int k) {
		deque<int> q;
		for (int i = 0; i < k; ++i) {
			while (!q.empty() and nums[q.back()] <= nums[i]) {
				q.pop_back();
			}
			q.push_back(i);
		}
		// store ans for first k ele
		vector<int> ans;
		ans.push_back(nums[q.front()]);

		// do for rest ele
		for (int i = k; i < nums.size(); ++i) {
			// remove invalid index
			while (!q.empty() and q.front() <= i - k) {
				q.pop_front();
			}
			// push ele if greater in win
			while (!q.empty() and nums[q.back()] <= nums[i]) {
				q.pop_back();
			}
			q.push_back(i);
			// store ans
			ans.push_back(nums[q.front()]);
		}
		return ans;
	}
};