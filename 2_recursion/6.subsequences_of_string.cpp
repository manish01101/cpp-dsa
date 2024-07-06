/*
abc -> "", a, b, c, ab, bc, ac, abc
*/
#include<iostream>
using namespace std;
#include<vector>

void solve(string str, string s, int i, vector<string>& ans) {
    // base case
    if (i >= str.length()) {
        if (s.length() > 0)
            ans.push_back(s);
        return;
    }
    solve(str, s, i + 1, ans);

    s += str[i];
    solve(str, s, i + 1, ans);
}

vector<string> subseq(string str) {
    vector<string> ans;
    string s;
    int i = 0;
    solve(str, s, i, ans);
    return ans;
}

int main() {
    vector<string> ans = subseq("man");
    for (auto i : ans) {
        cout << i << " ";
    }
}