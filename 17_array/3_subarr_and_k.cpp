
class Solution {
public:
    long long countSubarrays(vector<int>& nums, int k) {
        unordered_map<int, long long> prev, curr;
        long long count = 0;

        for (int num : nums) {
            curr.clear();

            // Subarray that starts at current element
            curr[num]++;

            // Extend previous subarrays
            for (auto &[val, freq] : prev) {
                curr[val & num] += freq;
            }

            // Add to answer
            count += curr[k];

            // Move to next iteration
            prev = curr;
        }

        return count;
    }
};
