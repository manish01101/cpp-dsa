#include<bits/stdc++.h>
using namespace std;

/*
? => matches with any single character
* => matches with any sequence of character, (i.e. empty, single, multiple)

fn => f(str, patter, i, j)


if (str[i] = pattern[j] || pattern[j] == '?')
	f(str, pattern, i-1, j-1)
else if (pattern[j] == '*')
	*empty = f(str, pattern, i, j-1)
	*single = f(str, pattern, i-1, j)

	return *empty || *single
else // not matched
	return false
*/

bool solve(string& str, string& pattern, int i, int j) {
	// base case
	if (i < 0 && j < 0) // both processed
		return true;
	if (i >= 0 && j < 0) // pattern processed
		return false;
	if (i < 0 && j >= 0) { // str processed
		for (int k = 0; k <= j; k++) {
			if (pattern[k] != '*') {
				return false;
			}
		}
		return true;
	}

	// matched
	if (str[i] == pattern[j] || pattern[j] == '?') {
		return solve(str, pattern, i - 1, j - 1);
	}
	else if (pattern[j] == '*') {
		return (solve(str, pattern, i, j - 1) || solve(str, pattern, i - 1, j));
	}
	else { // not matched
		return false;
	}
}


bool solveMem(string& str, string& pattern, int i, int j, vector<vector<int>>& dp) {
	// base case
	if (i < 0 && j < 0) // both processed
		return true;
	if (i >= 0 && j < 0) // pattern processed
		return false;
	if (i < 0 && j >= 0) { // str processed
		for (int k = 0; k <= j; k++) {
			if (pattern[k] != '*') {
				return false;
			}
		}
		return true;
	}

	// check if ans present
	if (dp[i][j] != -1)
		return dp[i][j];

	// matched
	if (str[i] == pattern[j] || pattern[j] == '?') {
		return dp[i][j] = solveMem(str, pattern, i - 1, j - 1, dp);
	}
	else if (pattern[j] == '*') {
		return dp[i][j] = (solveMem(str, pattern, i, j - 1, dp) || solveMem(str, pattern, i - 1, j, dp));
	}
	else { // not matched
		return false;
	}
}

// one based indexing
bool solveMemOne(string& str, string& pattern, int i, int j, vector<vector<int>>& dp) {
	// base case
	if (i == 0 && j == 0) // both processed, one based indexing
		return true;
	if (i > 0 && j == 0) // pattern processed
		return false;
	if (i == 0 && j > 0) { // str processed
		for (int k = 1; k <= j; k++) {
			if (pattern[k - 1] != '*') {
				return false;
			}
		}
		return true;
	}

	// check if ans present
	if (dp[i][j] != -1)
		return dp[i][j];

	// matched
	if (str[i - 1] == pattern[j - 1] || pattern[j - 1] == '?') {
		return dp[i][j] = solveMemOne(str, pattern, i - 1, j - 1, dp);
	}
	else if (pattern[j - 1] == '*') {
		return dp[i][j] = (solveMemOne(str, pattern, i, j - 1, dp) || solveMemOne(str, pattern, i - 1, j, dp));
	}
	else { // not matched
		return false;
	}
}

bool solveTab(string str, string pattern) {
	vector<vector<int>> dp(str.length() + 1, vector<int>(pattern.length() + 1, 0));
	// base case analyze
	dp[0][0] = true;
	for (int j = 1; j <= pattern.length(); j++) {
		bool flag = true;
		for (int k = 1; k <= j; k++) {
			if (pattern[k - 1] != '*') {
				flag = false;
				break;
			}
		}
		dp[0][j] = flag;
	}

	for (int i = 1; i <= str.length(); i++) {
		for (int j = 1; j <= pattern.length(); j++) {
			// matched
			if (str[i - 1] == pattern[j - 1] || pattern[j - 1] == '?') {
				dp[i][j] = dp[i - 1][j - 1];
			}
			else if (pattern[j - 1] == '*') {
				dp[i][j] = (dp[i][j - 1] || dp[i - 1][j]);
			}
			else { // not matched
				dp[i][j] = false;
			}
		}
	}
	return dp[str.length()][pattern.length()];
}



bool solveSpaceOpt(string str, string pattern) {
	vector<int> prev(pattern.length() + 1, 0);
	vector<int> curr(pattern.length() + 1, 0);
	// base case analyze
	prev[0] = true;
	for (int j = 1; j <= pattern.length(); j++) {
		bool flag = true;
		for (int k = 1; k <= j; k++) {
			if (pattern[k - 1] != '*') {
				flag = false;
				break;
			}
		}
		prev[j] = flag;
	}

	for (int i = 1; i <= str.length(); i++) {
		for (int j = 1; j <= pattern.length(); j++) {
			// matched
			if (str[i - 1] == pattern[j - 1] || pattern[j - 1] == '?') {
				curr[j] = prev[j - 1];
			}
			else if (pattern[j - 1] == '*') {
				curr[j] = (curr[j - 1] || prev[j]);
			}
			else { // not matched
				curr[j] = false;
			}
		}
		prev = curr;
	}
	return prev[pattern.length()];
}

bool isMatch(string s, string p) {
	/* --- recursion --- */
	// return solve(s, p, s.length() - 1, p.length() - 1);

	/* -- rec + mem -- */
	// vector<vector<int>> dp(s.length(), vector<int>(p.length(), -1));
	// return solveMem(s, p, s.length() - 1, p.length() - 1, dp);

	/* ---- rec + mem, one based indexing ---- */
	// vector<vector<int>> dp(s.length() + 1, vector<int>(p.length() + 1, -1));
	// return solveMemOne(s, p, s.length(), p.length(), dp);

	/* ---- tabulation ---- */
	// return solveTab(s, p);

	/* ---- space optimised ---- */
	return solveSpaceOpt(s, p);
}