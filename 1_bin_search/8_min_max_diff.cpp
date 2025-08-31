
// find min max diff b/w pairs of ele (not having same index)
bool isPossible(vector<int> &nums, int p, int minAllowed) {
	int cnt = 0;
	int index = 0;
	while(index < nuums.size()-1) {
		if(nums[index+1]-nums[index] <= minAllowed) {
			cnt++;
			index += 2;
		} else {
			index++;
		}
		if(cnt >= p) return true;
	}
	return false;
}
int minimize(vector<int> &nums, int p) {
	ranges::sort(nums);
	int s = 0;
	int e = nums.back()-nums.front();
	int ans = e;
	while(s <= e) {
		int mid = s + (e-s)/2;
		if(isPossible(nums, p, mid)) {
			ans = mid;
			e = mid - 1;
		} else {
			s = mid + 1;
		}
	}
	return ans;
}