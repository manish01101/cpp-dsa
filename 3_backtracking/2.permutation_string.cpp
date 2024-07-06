#include<iostream>
#include<vector>
using namespace std;

/*
permutation of "abc"
=> abc acb bac bca cab cba
abc => i @ a=> a swap with a => abc => i@b => b swap with b => abc
                                            => b swap with c => acb
            => a swap with b => bac => i@a => a swap with a => bac
                                            => a swap with c => bca
            => a swap with c => cba => i@b => b swap with b => cba
                                            => b swap with a => cab
*/
template <typename T>
void solve(vector<T> nums, vector<vector<T>>& ans, int i) {
    // base case
    if (i >= nums.size() - 1) { // i reached at last index, just store it & return
        ans.push_back(nums);
        return;
    }
    for (int j = i; j < nums.size(); j++) {
        swap(nums[i], nums[j]);
        solve(nums, ans, i + 1);
        // backtrack
        swap(nums[i], nums[j]);
    }
}
template <typename T>
vector<vector<T>> permute(vector<T>& nums) {
    vector<vector<T>> ans;
    int i = 0;
    solve(nums, ans, i);
    return ans;
}

int main() {
    vector<int> nums = { 1, 2, 3 };
    vector<vector<int>> ans = permute<int>(nums);
    vector<char> ch = { 'a', 'b', 'c' };
    vector<vector<char>> cha = permute<char>(ch);
    for (auto i : ans) {
        for (auto j : i) {
            cout << j;
        }
        cout << endl;
    }
    for (auto i : cha) {
        for (auto j : i) {
            cout << j;
        }
        cout << endl;
    }
}