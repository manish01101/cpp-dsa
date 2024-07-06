#include<iostream>
#include<vector>
using namespace std;

void solve(string digits, string output, int i, vector<string>& ans, string mapping[]) {
    // base case
    if (i >= digits.length()) {
        ans.push_back(output);
        return;
    }
    // extract number(digit)
    int number = digits[i] - '0';
    string value = mapping[number];

    // rec call for each char in value
    for (int j = 0; j < value.length(); j++) {
        output.push_back(value[j]);
        solve(digits, output, i + 1, ans, mapping);
        output.pop_back(); // backtrack remove the added char
    }
}

vector<string> letterCombination(string digits) {
    vector<string> ans;
    if (digits.length() == 0) {
        return ans;
    }
    string output;
    int i = 0;
    string mapping[10] = { "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
    solve(digits, output, i, ans, mapping);
    return ans;
}

int main() {
    string dit = "23";
    vector<string> ans = letterCombination(dit);
    for (auto i : ans) {
        cout << i << " ";
    }
    cout << endl;
}