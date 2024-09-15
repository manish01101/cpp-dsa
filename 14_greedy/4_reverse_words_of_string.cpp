#include<bits/stdc++.h>
using namespace std;


string reverseWords(string S) {
	string ans = "";
	string temp = "";

	for (int i = S.length() - 1; i >= 0; i--) {
		if (S[i] == '.') {
			reverse(temp.begin(), temp.end());
			ans += temp;
			ans += '.';
			temp = "";
		}
		else {
			temp.push_back(S[i]);
		}
	}
	// handling first word
	reverse(temp.begin(), temp.end());
	ans += temp;
	return ans;
}