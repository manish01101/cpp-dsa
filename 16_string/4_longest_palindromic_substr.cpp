#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

// 1️⃣ Brute Force O(n³)
string longestPalindromeBrute(string s) {
    int n = s.size();
    string longest = "";
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            string substr = s.substr(i, j - i + 1);
            string rev = substr;
            reverse(rev.begin(), rev.end());
            if (substr == rev && substr.size() > longest.size()) {
                longest = substr;
            }
        }
    }
    return longest;
}

// 2️⃣ Expand Around Center O(n²)
string expandFromCenter(string s, int left, int right) {
    while (left >= 0 && right < s.size() && s[left] == s[right]) {
        left--;
        right++;
    }
    return s.substr(left + 1, right - left - 1);
}

string longestPalindromeCenter(string s) {
    string longest = "";
    for (int i = 0; i < s.size(); i++) {
        string odd = expandFromCenter(s, i, i);
        string even = expandFromCenter(s, i, i + 1);
        string longer = (odd.size() > even.size()) ? odd : even;
        if (longer.size() > longest.size()) {
            longest = longer;
        }
    }
    return longest;
}

// 3️⃣ Manacher’s Algorithm O(n)
string longestPalindromeManacher(string s) {
    if (s.empty()) return "";

    string t = "^";
    for (char c : s) t += "#" + string(1, c);
    t += "#$";

    int n = t.size();
    vector<int> p(n, 0);
    int center = 0, right = 0;

    for (int i = 1; i < n - 1; i++) {
        int mirror = 2 * center - i;
        if (i < right) p[i] = min(right - i, p[mirror]);

        while (t[i + (1 + p[i])] == t[i - (1 + p[i])]) p[i]++;

        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }
    }

    int maxLen = 0, centerIndex = 0;
    for (int i = 1; i < n - 1; i++) {
        if (p[i] > maxLen) {
            maxLen = p[i];
            centerIndex = i;
        }
    }

    int start = (centerIndex - maxLen) / 2;
    return s.substr(start, maxLen);
}

string generateRandomString(int length) {
    static const string chars = "abcdefghijklmnopqrstuvwxyz";
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, chars.size() - 1);

    string s;
    s.reserve(length);
    for (int i = 0; i < length; i++) {
        s += chars[dis(gen)];
    }
    return s;
}

int main() {
    // string s = "babadjjjhvgvhgvgfvhgvkhjblhfhjhjbjjkhbadabab";

    // Large random string test
    string s = generateRandomString(5000);
    cout << s << endl;

    // Brute Force
    auto start = high_resolution_clock::now();
    string res1 = longestPalindromeBrute(s);
    auto end = high_resolution_clock::now();
    cout << "Brute Force: " << res1
        << " | Time: " << duration_cast<microseconds>(end - start).count() << " us\n";

    // Expand Around Center
    start = high_resolution_clock::now();
    string res2 = longestPalindromeCenter(s);
    end = high_resolution_clock::now();
    cout << "Expand Around Center: " << res2
        << " | Time: " << duration_cast<microseconds>(end - start).count() << " us\n";

    // Manacher's Algorithm
    start = high_resolution_clock::now();
    string res3 = longestPalindromeManacher(s);
    end = high_resolution_clock::now();
    cout << "Manacher's Algorithm: " << res3
        << " | Time: " << duration_cast<microseconds>(end - start).count() << " us\n";
}
