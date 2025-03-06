#include<iostream>
#include<vector>
using namespace std;
/*
approach :
    ->take first str
    ->compare each char of first str with char of remaining str
    ->if match store char & comp next char
    ->if not break
*/
// using loop; tc: m*n, sc: 1
string longestCommonPrefix(vector<string>& arr, int n) {
    string ans = "";
    //for traversing all char of first string
    for (int i = 0; i < arr[0].length(); i++) {
        char ch = arr[0][i];
        bool match = true;
        //for comparing char with remaing string
        for (int j = 1; j < n; j++) {
            // if not match
            if (arr[j].size() < i || ch != arr[j][i]) {
                match = false;
                break;
            }
        }
        if (match == false)
            break;
        else
            ans.push_back(ch);
    }
    return ans;
}


// REFACTORED CODE
class TrieNode {
public:
    char data;
    TrieNode* children[26];
    int childCount;
    bool isTerminal;

    TrieNode(char ch) : data(ch), childCount(0), isTerminal(false) {
        fill(begin(children), end(children), nullptr);
    }
};

class Trie {
private:
    TrieNode* root;

    void insertUtil(TrieNode* root, const string& word, int index) {
        if (index == word.length()) {
            root->isTerminal = true;
            return;
        }
        int charIndex = word[index] - 'a';
        if (!root->children[charIndex]) {
            root->children[charIndex] = new TrieNode(word[index]);
            root->childCount++;
        }
        insertUtil(root->children[charIndex], word, index + 1);
    }

public:
    Trie() : root(new TrieNode('\0')) {}

    void insertWord(const string& word) {
        insertUtil(root, word, 0);
    }

    string longestCommonPrefix(const string& firstWord) {
        string ans;
        TrieNode* curr = root;
        for (char ch : firstWord) {
            int index = ch - 'a';
            if (curr->childCount == 1 && !curr->isTerminal) {
                ans.push_back(ch);
                curr = curr->children[index];
            } else {
                break;
            }
        }
        return ans;
    }
};

string trieLongestCommonPrefix(vector<string>& words) {
    if (words.empty()) return "";
    
    Trie trie;
    for (const string& word : words) {
        trie.insertWord(word);
    }
    return trie.longestCommonPrefix(words[0]);
}

int main() {
    vector<string> words = { "manish", "man" };
    cout << "Longest Common Prefix: " << trieLongestCommonPrefix(words) << endl;
    return 0;
}


// using trie tc: m*n sc: m*n
class TrieNode {
public:
    char data;
    TrieNode* children[26];
    int childCount;
    bool isTerminal;

    TrieNode(char ch) {
        data = ch;
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
        childCount = 0;
        isTerminal = false;
    }
};
class Trie {
public:
    TrieNode* root;
    Trie(char ch) {
        root = new TrieNode(ch);
    }
    void insertUtil(TrieNode* root, string word) {
        //base case
        if (word.length() == 0) {
            root->isTerminal = true;
            return;
        }
        //assume word will be in lower
        int index = word[0] - 'a';
        TrieNode* child;

        // char is present
        if (root->children[index] != nullptr) {
            child = root->children[index];
        }
        // char is absent
        else {
            child = new TrieNode(word[0]);
            root->childCount++;
            root->children[index] = child;
        }

        //recursion
        insertUtil(child, word.substr(1));

    }
    // T.C INSERT O(LENGTH OF WORD)
    void insertWord(string word) {
        insertUtil(root, word);
    }
    void lowComPre(string str, string& ans) {
        for (int i = 0; i < str.length(); i++) {
            char ch = str[i];
            if (root->childCount == 1) {
                ans.push_back(ch);
                //move to next child
                int index = ch - 'a';
                root = root->children[index];
            }
            else break;
            if (root->isTerminal) break;
        }
    }
};

string trieLongestCommonPrefix(vector<string>& arr, int n) {
    Trie* t = new Trie('\0');
    //insert all str into trie
    for (int i = 0; i < n; i++) {
        t->insertWord(arr[i]);
    }
    string first = arr[0];
    string ans = "";

    t->lowComPre(first, ans);
    return ans;
}

int main() {
    vector<string> v = { "manish", "man" };
    string ans = longestCommonPrefix(v, 2);
    cout << " answer: " << ans << "\n";
    string anstrie = trieLongestCommonPrefix(v, 2);
    cout << " answer: " << anstrie << "\n";
}