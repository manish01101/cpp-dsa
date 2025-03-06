#include <iostream>
#include <vector>
using namespace std;

class TrieNode {
public:
    char data;
    vector<TrieNode*> children;
    bool isTerminal;

    TrieNode(char ch) : data(ch), children(26, nullptr), isTerminal(false) {}
};

class Trie {
private:
    TrieNode* root;

    void insertUtil(TrieNode* root, const string& word, int index) {
        if (index == word.length()) {
            root->isTerminal = true;
            return;
        }
        int charIndex = word[index] - 'A';
        if (!root->children[charIndex]) {
            root->children[charIndex] = new TrieNode(word[index]);
        }
        insertUtil(root->children[charIndex], word, index + 1);
    }

    bool searchUtil(TrieNode* root, const string& word, int index) {
        if (index == word.length()) return root->isTerminal;
        int charIndex = word[index] - 'A';
        if (!root->children[charIndex]) return false;
        return searchUtil(root->children[charIndex], word, index + 1);
    }

    bool prefixUtil(TrieNode* root, const string& prefix, int index) {
        if (index == prefix.length()) return true;
        int charIndex = prefix[index] - 'A';
        if (!root->children[charIndex]) return false;
        return prefixUtil(root->children[charIndex], prefix, index + 1);
    }

public:
    Trie() : root(new TrieNode('\0')) {}

    void insertWord(const string& word) {
        insertUtil(root, word, 0);
    }

    bool searchWord(const string& word) {
        return searchUtil(root, word, 0);
    }

    bool startsWith(const string& prefix) {
        return prefixUtil(root, prefix, 0);
    }
};

int main() {
    Trie t;
    t.insertWord("ABCD");
    t.insertWord("DEED");
    t.insertWord("FFFF");
    t.insertWord("WERE");
    cout << "Present or not: " << t.searchWord("DDEED") << endl;
    return 0;
}





class TrieNode {
public:
    char data;
    TrieNode* children[26];
    bool isTerminal;

    TrieNode(char ch) {
        data = ch;
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
        isTerminal = false;
    }
};

class Trie {
private:
    TrieNode* root;
    
    // inserting
    void insertUtil(TrieNode* root, string word) {
        //base case
        if (word.length() == 0) {
            root->isTerminal = true;
            return;
        }

        int index = word[0] - 'A'; //assume word will be in caps
        TrieNode* child;

        if (root->children[index] != nullptr) { // char is present
            child = root->children[index];
        }
        else {
            child = new TrieNode(word[0]);  // char is absent
            root->children[index] = child;
        }

        insertUtil(child, word.substr(1));
    }
    // searching
    bool searchUtil(TrieNode* root, string word) {
        //base case
        if (word.length() == 0) {
            return root->isTerminal;
        }
        int index = word[0] - 'A';
        TrieNode* child;

        if (root->children[index] != nullptr) {  // char is present
            child = root->children[index];
        }
        // char is absent
        else {
            return false;
        }

        // recursion
        return searchUtil(child, word.substr(1));
    }
    // if any word start with given prefix
    bool prefixUtil(TrieNode* root, string word) {
        //base case
        if (word.length() == 0) {
            return true;
        }
        int index = word[0] - 'A';
        TrieNode* child;

        // char is present
        if (root->children[index] != nullptr) {
            child = root->children[index];
        }
        // char is absent
        else {
            return false;
        }

        // recursion
        return prefixUtil(child, word.substr(1));
    }

public:
    Trie() {
        root = new TrieNode('\0');
    }
    // T.C INSERT O(LENGTH OF WORD)
    void insertWord(string word) {
        insertUtil(root, word);
    }
    // T.C SEARCH = O(LENGTH OF WORD)
    bool searchWord(string word) {
        return searchUtil(root, word);
    }
    bool startsWith(string prefix) {
        return prefixUtil(root, prefix);
    }
};

int main() {

    Trie* t = new Trie();
    t->insertWord("ABCD");
    t->insertWord("DEED");
    t->insertWord("FFFF");
    t->insertWord("WERE");
    cout << "present or not " << t->searchWord("DDEED") << endl;
    return 0;
}