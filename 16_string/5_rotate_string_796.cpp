/*Given two strings s and goal, return true if and only if s can become goal after some number of shifts on s.
A shift on s consists of moving the leftmost character of s to the rightmost position.
For example, if s = "abcde", then it will be "bcdea" after one shift.*/
class Solution {
	vector<int> computeLPS(string& pattern) {
		int len = pattern.size();
		vector<int> lps(len, 0);
		int i = 0, j = 1;
		while (j < len) {
			if (pattern[i] == pattern[j]) {
				lps[j] = i + 1;
				i++; j++;
			}
			else {
				if (i > 0) {
					i = lps[i - 1];
				}
				else {
					lps[j] = 0;
					j++;
				}
			}
		}
		return lps;
	}
	bool KMP_search(string& text, string& pattern) {
		int t_size = text.size();
		int p_size = pattern.size();

		vector<int> lps = computeLPS(pattern);
		int i = 0;
		int j = 0;
		while (i < t_size) {
			if (text[i] == pattern[j]) {
				i++; j++;
			}
			if (j == p_size) {
				return true;
			}
			else if (i < t_size and text[i] != pattern[j]) {
				if (j > 0) {
					j = lps[j - 1];
				}
				else {
					i++;
				}
			}
		}
		return false;
	}
public:
	bool rotateString(string s, string goal) {
		if (s.size() != goal.size())
			return false;
		string temp = s + s;
		return KMP_search(temp, goal);
	}
};