#include <iostream>
#include <vector>
using namespace std;
/*
(Knuth–Morris–Pratt) String Matching Algorithm

🔷 Part 1: Build the LPS (Longest Prefix Suffix) Array
Let pattern be the pattern of length m.

Steps:

Initialize:
lps[0] = 0 (no proper prefix for first character)
len = 0 (length of previous longest prefix suffix)
Start from i = 1
Repeat while i < m:
If pattern[i] == pattern[len]:
Increment len
Set lps[i] = len
Increment i
Else:
If len != 0:
Set len = lps[len - 1] (fallback)
Else:
Set lps[i] = 0
Increment i
🔷 Part 2: Pattern Matching Using LPS
Let text be the text of length n.

Steps:

Initialize:
i = 0 (index for text)
j = 0 (index for pattern)
Repeat while i < n:
If text[i] == pattern[j]:
Increment both i and j
If j == m (complete pattern matched):
Report match at index i - j
Set j = lps[j - 1] (look for next match)
Else if i < n and text[i] != pattern[j]:
If j != 0:
Set j = lps[j - 1] (use LPS to avoid redundant comparisons)
Else:
Increment i


🧠 Time Complexity:
Preprocessing (LPS array): O(m)
Pattern search: O(n)
Total: O(n + m)

*/

// Step 1: Build the LPS (Longest Prefix Suffix) array
vector<int> computeLPS(string s) {
    int len = s.length();
    vector<int> lps(len, 0);
    int i = 0; // length of the previous longest prefix suffix
    int j = 1;

    while (j < len) {
        if (s[i] == s[j]) {
            lps[j] = i + 1;
            i++; j++;
        }
        else {
            if (i > 0) {
                i = lps[i - 1]; // check the prev one index val
            }
            else {
                lps[j] = 0;
                j++;
            }
        }
    }
    return lps;
}

// Step 2: Perform KMP pattern matching
void KMP_Search(const string& text, const string& pattern) { // O(m+n)
    int t_size = text.size();
    int p_size = pattern.size();

    vector<int> lps = computeLPS(pattern);
    int i = 0; // index for text
    int j = 0; // index for pattern

    while (i < t_size) {
        if (pattern[j] == text[i]) {
            i++; j++;
        }
        if (j == p_size) {
            cout << "Pattern found at index " << (i - j) << endl;
            j = lps[j - 1]; // move to next possible match
        }
        else if (i < t_size && pattern[j] != text[i]) {
            if (j > 0)
                j = lps[j - 1]; // fall back using LPS
            else
                i++;
        }
    }
}

// Test it
int main() {
    string text = "ababcababcabc";
    string pattern = "ababc";

    KMP_Search(text, pattern);
    return 0;
}
