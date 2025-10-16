#include <iostream>
#include <vector>
using namespace std;
/*
✅ Rabin-Karp Algorithm Overview

It uses a rolling hash to efficiently compare substrings.
Best-case time: O(n + m)
Worst-case (due to hash collisions): O(nm)

total_char_type for alphabet = 26, all char = 256
hash of pattern
    hash = summ.[letter_val * total_char_type^pos_of_char]

updation
    b = hash_of_text
    c = b - remove_letter_val * total_char_type^MSB
    d = c * total_char_type => right shift operation
    e = d + letter_val * total_char_type^LSB

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

        int h = 1; // h would be "pow(d, M-1)%q
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


/*
rolling hash(as in each window, subtracting and adding)
use unique hash method so that each window get unique hash, this makes it efficient
steps:
    - calculate hash for pattern
    - calculate hash for 1st window in text
    - repeat untill text ends
        - if hash(pattern) == hash(text in window) -> match char by char
        - subtract left most from hash(text_window)
        (- shift entire hash(text_window) by 1 unit to left)
        - add new char added to window
*/
