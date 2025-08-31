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
vector<int> computeLPS(const string& pattern) {
    int m = pattern.size();
    vector<int> lps(m, 0);

    int len = 0; // length of the previous longest prefix suffix
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1]; // fall back in the pattern
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

// Step 2: Perform KMP pattern matching
void KMP_Search(const string& text, const string& pattern) {
    int n = text.size();
    int m = pattern.size();

    vector<int> lps = computeLPS(pattern);
    int i = 0; // index for text
    int j = 0; // index for pattern

    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            cout << "Pattern found at index " << (i - j) << endl;
            j = lps[j - 1]; // move to next possible match
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0)
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
