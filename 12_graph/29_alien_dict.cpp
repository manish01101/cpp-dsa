/*
A new alien language uses the English alphabet, but the order of letters is unknown. You are given a list of words[] from the alien language’s dictionary, where the words are claimed to be sorted lexicographically according to the language’s rules.

Your task is to determine the correct order of letters in this alien language based on the given words. If the order is valid, return a string containing the unique letters in lexicographically increasing order as per the new language's rules. If there are multiple valid orders, return any one of them.

However, if the given arrangement of words is inconsistent with any possible letter ordering, return an empty string ("").

A string a is lexicographically smaller than a string b if, at the first position where they differ, the character in a appears earlier in the alien language than the corresponding character in b. If all characters in the shorter word match the beginning of the longer word, the shorter word is considered smaller.
Note: Your implementation will be tested using a driver code. It will print true if your returned order correctly follows the alien language’s lexicographic rules; otherwise, it will print false.

Examples:

Input: words[] = ["baa", "abcd", "abca", "cab", "cad"]
Output: true
Explanation: A possible corrct order of letters in the alien dictionary is "bdac".
The pair "baa" and "abcd" suggests 'b' appears before 'a' in the alien dictionary.
The pair "abcd" and "abca" suggests 'd' appears before 'a' in the alien dictionary.
The pair "abca" and "cab" suggests 'a' appears before 'c' in the alien dictionary.
The pair "cab" and "cad" suggests 'b' appears before 'd' in the alien dictionary.
So, 'b' → 'd' → 'a' → 'c' is a valid ordering.
*/


class Solution {
public:
	string findOrder(vector<string>& words) {
		unordered_map<char, unordered_set<char>> adjList;
		unordered_map<char, int> inDegree;
		for (int i = 0; i < words.size() - 1; ++i) {
			string word1 = words[i], word2 = words[i + 1];
			int minLen = min(word1.length(), word2.length());
			bool isDiff = false;
			for (int j = 0; j < minLen; ++j) {
				if (word1[j] != word2[j]) {
					if (adjList[word1[j]].find(word2[j]) == adjList[word1[j]].end()) {
						adjList[word1[j]].insert(word2[j]);
						inDegree[word2[j]]++;
					}
					isDiff = true;
					break;
				}
			}
			// word1 is a prefix of word2 but longer
			if (!isDiff and word1.length() > word2.length()) {
				return "";
			}
		}
		// total distinct char
		unordered_set<char> allChars;
		for (auto& word : words) {
			for (auto ch : word) {
				allChars.insert(ch);
			}
		}

		// perform topo sort
		queue<char> q;
		string ans;
		for (auto ele : allChars) {
			if (inDegree[ele] == 0) {
				q.push(ele);
			}
		}
		while (!q.empty()) {
			char curr = q.front(); q.pop();
			ans += curr;
			for (auto nbr : adjList[curr]) {
				inDegree[nbr]--;
				if (inDegree[nbr] == 0) {
					q.push(nbr);
				}
			}
		}
		if (ans.size() != allChars.size()) {
			return "";
		}
		return ans;
	}
};
