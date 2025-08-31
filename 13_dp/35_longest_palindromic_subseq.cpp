#include<bits/stdc++.h>
using namespace std;

/*
given str => bbbab
reverse str => babbb

find longest common subseq of str & revstr
*/

int solveSpaceOpt(string a, string b) {
	vector<int> curr(b.length() + 1, 0);
	vector<int> next(b.length() + 1, 0);

	for (int i = a.length() - 1; i >= 0; i--) {
		for (int j = b.length() - 1; j >= 0; j--) {
			int ans = 0;
			if (a[i] == b[j]) {
				ans = 1 + next[j + 1];
			}
			else {
				ans = max(next[j], curr[j + 1]);
			}
			curr[j] = ans;
		}
		next = curr;
	}
	return next[0];
}

int longestPalindromeSubseq(string s) {
	string revStr = s;
	reverse(revStr.begin(), revStr.end());
	return solveSpaceOpt(s, revStr);
}



// Recursive Approach
int solveRecursive(string& s, int i, int j) {
    if (i > j) return 0; // Base case: invalid range
    if (i == j) return 1; // Base case: single character is a palindrome
    if (s[i] == s[j]) {
        return 2 + solveRecursive(s, i + 1, j - 1);
    } else {
        return max(solveRecursive(s, i + 1, j), solveRecursive(s, i, j - 1));
    }
}

// Recursive + Memoization (Top-Down DP)
int solveMemo(string& s, int i, int j, vector<vector<int>>& dp) {
    if (i > j) return 0;
    if (i == j) return 1;
    if (dp[i][j] != -1) return dp[i][j];
    if (s[i] == s[j]) {
        dp[i][j] = 2 + solveMemo(s, i + 1, j - 1, dp);
    } else {
        dp[i][j] = max(solveMemo(s, i + 1, j, dp), solveMemo(s, i, j - 1, dp));
    }
    return dp[i][j];
}

// Tabulation (Bottom-Up DP)
int solveTabulation(string& s) {
    int n = s.length();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    // Base case: single characters are palindromes
    for (int i = 0; i < n; i++) dp[i][i] = 1;

    // Fill the table for substrings of length 2 and more
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            if (s[i] == s[j]) {
                dp[i][j] = 2 + dp[i + 1][j - 1];
            } else {
                dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[0][n - 1];
}

// Space Optimization
int solveSpaceOptimized(string& s) {
    int n = s.length();
    vector<int> prev(n, 0), curr(n, 0);

    // Base case: single characters are palindromes
    for (int i = n - 1; i >= 0; i--) {
        curr[i] = 1; // Single character
        for (int j = i + 1; j < n; j++) {
            if (s[i] == s[j]) {
                curr[j] = 2 + prev[j - 1];
            } else {
                curr[j] = max(prev[j], curr[j - 1]);
            }
        }
        prev = curr;
    }
    return curr[n - 1];
}

int longestPalindromeSubseq2(string s) {
    // Recursive
    // return solveRecursive(s, 0, s.length() - 1);

    // Memoization
    // vector<vector<int>> dp(s.length(), vector<int>(s.length(), -1));
    // return solveMemo(s, 0, s.length() - 1, dp);

    // Tabulation
    return solveTabulation(s);

    // Space Optimization
    // return solveSpaceOptimized(s);
}

int main() {
    string s = "bbbab";
    cout << "Longest Palindromic Subsequence Length: " << longestPalindromeSubseq2(s) << endl;
    return 0;
}