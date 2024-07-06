#include<iostream>
#include<vector>
using namespace std;

/*
find powerset of set
set: {1,2,3}
o/p powerset: {{}, {1}, {2}, {3}, {1,2},{2,3},{1,3}, {1,2,3}}
*/
void solve(vector<int> nums, vector<int> output, int index, vector<vector<int>>& ans) {
    // base case
    if (index >= nums.size()) {
        ans.push_back(output);
        return;
    }
    // exclude
    solve(nums, output, index + 1, ans);

    // include
    int element = nums[index];
    output.push_back(element);
    solve(nums, output, index + 1, ans);
}

vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> ans;
    vector<int> output;
    int index = 0;
    solve(nums, output, index, ans);
    return ans;
}

int main() {
    vector<int> nums;
    nums.push_back(1);
    nums.push_back(2);
    vector<vector<int>> ans = subsets(nums);
}