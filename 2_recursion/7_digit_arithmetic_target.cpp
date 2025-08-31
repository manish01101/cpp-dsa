#include <bits/stdc++.h>
using namespace std;
/*Given a string num that contains only digits and an integer target, return all possibilities to insert the binary operators '+', '-', and/or '*' between the digits of num so that the resultant expression evaluates to the target value.

Note that operands in the returned expressions should not contain leading zeros.*/
class Solution {
    void solve(string& num, int target, long long total, long long lastNumber, string str, int index, vector<string>& ans) {
        if (index == num.length()) {
            if (total == target) {
                ans.push_back(str);
            }
            return;
        }

        char ch = num[index];
        int chVal = ch - '0';

        if (index == 0) {
            // First character, just add without any operator
            solve(num, target, chVal, chVal, str + ch, index + 1, ans);
        }
        else {
            // +
            solve(num, target, total + chVal, chVal, str + '+' + ch, index + 1, ans);
            // -
            solve(num, target, total - chVal, -chVal, str + '-' + ch, index + 1, ans);
            // *
            solve(num, target, (total - lastNumber) + (lastNumber * chVal), lastNumber * chVal, str + '*' + ch, index + 1, ans);
        }
    }

public:
    vector<string> fn(string num, int target) {
        vector<string> ans;
        if (num.empty()) return ans;
        long long total = 0, lastNumber = 0;
        string str = "";
        int index = 0;
        solve(num, target, total, lastNumber, str, index, ans);
        return ans;
    }
};

int main() {
    Solution s;
    vector<string> ans = s.fn("1622", 11);
    if (ans.size() == 0) cout << "not possible" << endl;
    for (auto a : ans) {
        cout << a << endl;
    }
}