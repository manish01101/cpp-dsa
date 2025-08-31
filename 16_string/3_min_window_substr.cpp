#include<bits/stdc++.h>
using namespace std;
// approach 1 -> findout all substring & match with them O(n^2)
// approach 2
class Solution {
#define SIZE 256+2
	bool equalFreq(vector<int>& curr, vector<int>& freq) {//Check frequency of current window with freq(t)
		for (int i = 0;i < SIZE;++i)
			if (freq[i] > 0 and curr[i] < freq[i])
				return false;
		return true;
	}
public:
	string minWindow(string s, string t) {
		int n = s.size();
		if (n < t.size())
			return "";

		vector<int> freq(SIZE, 0);
		for (char& c : t)//Find freq(t)
			freq[c]++;

		int l = 0, r = 0;//left and right pointers of sliding window
		int minWin = INT_MAX;
		string ans = "";
		vector<int> curr(SIZE, 0);

		while (r < n) { //run till end of string
			curr[s[r]]++;
			if (equalFreq(curr, freq)) {//If we have all chars of t in our curr window
				do {    //move left ptr to as right as possible to minimize window size
					curr[s[l]]--;
					l++;
				} while (equalFreq(curr, freq));//Run until curr no more matches t
				if (minWin > r - l + 2) {//If curr window size is less than already know minWin size
					minWin = r - l + 2;
					ans = s.substr(l - 1, minWin);
				}
			}
			r++;
		}
		return ans;
	}
};