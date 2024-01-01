
#include<iostream>
using namespace std;

class TrieNode {
    public:
        char data;
        TrieNode* children[26];
        bool isTerminal;

        TrieNode(char ch) {
            data = ch;
            for(int i=0; i<26; i++) {
                children[i] = NULL;
            }
            isTerminal = false;
        }
};
class Trie {
    public:
        TrieNode* root;

        Trie() {
            root = new TrieNode('\0');
        }
        void insertUtil(TrieNode* root, string word) {
            //base case
            if(word.length() == 0) {
                root->isTerminal = true;
                return;
            }
            //assume word will be in caps
            int index = word[0] - 'A';
            TrieNode* child;

            // char is present
            if(root->children[index] != NULL) {
                child = root->children[index];
            }
            // char is absent
            else {
                child = new TrieNode(word[0]);
                root->children[index] = child;
            }

            //recursion
            insertUtil(child, word.substr(1));
            
        }
        // T.C INSERT O(LENGTH OF WORD)
        void insertWord(string word) {
            insertUtil(root, word);
        }

        // searching
        bool searchUtil(TrieNode* root, string word) {
            //base case
            if(word.length() == 0) {
                return root->isTerminal;
            }
            int index = word[0] - 'A';
            TrieNode* child;

            // char is present
            if(root->children[index] != NULL) {
                child = root->children[index];
            }
            // char is absent
            else {
                return false;
            }

            // recursion
            return searchUtil(child, word.substr(1));
        }
        // T.C SEARCH = O(LENGTH OF WORD)
        bool searchWord(string word) {
            return searchUtil(root, word);
        }



        // if any word start with given prefix
        bool prefixUtil(TrieNode* root, string word) {
            //base case
            if(word.length() == 0) {
                return true;
            }
            int index = word[0] - 'A';
            TrieNode* child;

            // char is present
            if(root->children[index] != NULL) {
                child = root->children[index];
            }
            // char is absent
            else {
                return false;
            }

            // recursion
            return prefixUtil(child, word.substr(1));
        }
        bool startsWith(string prefix) {
            return prefixUtil(root, prefix);
        }
};

int main() {

    Trie *t = new Trie();
    t->insertWord("ABCD");
    t->insertWord("DEED");
    t->insertWord("FFFF");
    t->insertWord("WERE");
    cout << "present or not " << t->searchWord("DDEED") << endl;
    return 0;
}