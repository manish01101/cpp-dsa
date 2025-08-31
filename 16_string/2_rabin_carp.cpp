#include <iostream>
#include <vector>
using namespace std;
/*
✅ Rabin-Karp Algorithm Overview

It uses a rolling hash to efficiently compare substrings.
Best-case time: O(n + m)
Worst-case (due to hash collisions): O(nm)
*/
class RabinKarp {
private:
    const int d = 256;        // number of characters in input alphabet
    const int q = 101;        // a prime number to mod hash values

public:
    vector<int> search(const string& text, const string& pattern) {
        int n = text.length();
        int m = pattern.length();
        vector<int> result;

        if (m > n) return result;

        int h = 1;
        for (int i = 0; i < m - 1; i++)
            h = (h * d) % q;

        int p = 0; // hash value for pattern
        int t = 0; // hash value for text window

        // Initial hash values for pattern and first window of text
        for (int i = 0; i < m; i++) {
            p = (d * p + pattern[i]) % q;
            t = (d * t + text[i]) % q;
        }

        // Slide the pattern over text one by one
        for (int i = 0; i <= n - m; i++) {
            // If hash values match, check characters one by one
            if (p == t) {
                bool match = true;
                for (int j = 0; j < m; j++) {
                    if (text[i + j] != pattern[j]) {
                        match = false;
                        break;
                    }
                }
                if (match)
                    result.push_back(i); // Match found
            }

            // Compute hash for next window
            if (i < n - m) {
                t = (d * (t - text[i] * h) + text[i + m]) % q;

                // We might get negative hash, convert it to positive
                if (t < 0)
                    t = t + q;
            }
        }

        return result;
    }
};

// Test it
int main() {
    RabinKarp rk;
    string text = "ababcabcababd";
    string pattern = "ababd";

    vector<int> matches = rk.search(text, pattern);

    for (int i : matches)
        cout << "Pattern found at index " << i << endl;

    return 0;
}
