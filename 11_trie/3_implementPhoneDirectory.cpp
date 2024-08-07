#include<iostream>
#include<vector>

using namespace std;
/*
tc: o(n*m2), sc: o(n*m)
*/

// using trie
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



    void printSuggestions(TrieNode* curr, vector<string>& temp, string prefix) {
        if (curr->isTerminal) {
            temp.push_back(prefix);
        }

        for (char ch = 'a'; ch <= 'z'; ch++) {
            TrieNode* next = curr->children[ch - 'a'];

            if (next != nullptr) {
                prefix.push_back(ch);
                printSuggestions(next, temp, prefix);
                prefix.pop_back();
            }
        }
    }
    //fn getsuggestions
    vector< vector<string> > getSuggestions(string str) {
        TrieNode* prev = root;
        vector<vector<string>> output;
        string prefix = "";

        for (int i = 0; i < str.length(); i++) {
            char lastch = str[i];

            prefix.push_back(lastch);

            //check for last char
            TrieNode* curr = prev->children[lastch - 'a'];

            //if not found
            if (curr == nullptr)
                break;
            //if found
            vector<string> temp;
            printSuggestions(curr, temp, prefix);

            output.push_back(temp);
            temp.clear();
            prev = curr;
        }
        return output;
    }
};

vector<vector<string>> phoneDirectory(vector<string>& contactList, string& queryStr) {

    //creation of trie
    Trie* t = new Trie('\0');

    //insert all contact in trie
    for (int i = 0; i < contactList.size(); i++) {
        string str = contactList[i];
        t->insertWord(str);
    }
    //return ans
    return t->getSuggestions(queryStr);
}