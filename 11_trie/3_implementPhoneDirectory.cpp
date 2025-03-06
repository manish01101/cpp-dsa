#include<iostream>
#include<vector>

using namespace std;
/*
tc: o(n*m2), sc: o(n*m)
*/

// REFACTORED
// Trie Node structure
class TrieNode {
public:
    char data;
    TrieNode* children[26]; // Array to store 26 lowercase English letters
    int childCount; // Keeps track of the number of children
    bool isTerminal; // Marks the end of a word

    TrieNode(char ch) : data(ch), childCount(0), isTerminal(false) {
        fill(begin(children), end(children), nullptr); // Initialize children to nullptr
    }
};

class Trie {
private:
    TrieNode* root; // Root of the Trie

    // Recursive helper function to insert a word into the Trie
    void insertUtil(TrieNode* root, const string& word, int index) {
        if (index == word.length()) {
            root->isTerminal = true; // Mark the end of the word
            return;
        }
        int charIndex = word[index] - 'a'; // Get index for the character
        if (!root->children[charIndex]) { // If character not present, create new TrieNode
            root->children[charIndex] = new TrieNode(word[index]);
            root->childCount++;
        }
        insertUtil(root->children[charIndex], word, index + 1); // Recur for next character
    }

    // Helper function to collect all words with the given prefix
    void printSuggestions(TrieNode* curr, vector<string>& temp, string& prefix) {
        if (curr->isTerminal) {
            temp.push_back(prefix); // If terminal node, add the word to suggestions
        }
        for (char ch = 'a'; ch <= 'z'; ch++) { // Iterate over all possible child nodes
            TrieNode* next = curr->children[ch - 'a'];
            if (next) {
                prefix.push_back(ch); // Add character to prefix
                printSuggestions(next, temp, prefix);
                prefix.pop_back(); // Remove character after recursion
            }
        }
    }

public:
    Trie() : root(new TrieNode('\0')) {} // Initialize root with null character

    // Function to insert a word into the Trie
    void insertWord(const string& word) {
        insertUtil(root, word, 0);
    }

    // Function to get word suggestions based on the given prefix
    vector<vector<string>> getSuggestions(const string& query) {
        TrieNode* curr = root;
        vector<vector<string>> output;
        string prefix = "";
        for (char ch : query) {
            prefix.push_back(ch);
            TrieNode* next = curr->children[ch - 'a'];
            if (!next) break; // If prefix not found, stop processing
            vector<string> temp;
            printSuggestions(next, temp, prefix); // Find all suggestions for current prefix
            output.push_back(temp);
            curr = next;
        }
        return output;
    }
};

// Function to process phone directory and get suggestions for a given query
vector<vector<string>> phoneDirectory(vector<string>& contactList, const string& queryStr) {
    Trie trie;
    for (const string& contact : contactList) {
        trie.insertWord(contact); // Insert each contact into the Trie
    }
    return trie.getSuggestions(queryStr); // Retrieve suggestions
}

int main() {
    vector<string> contacts = {"manish", "man", "mango", "map"}; // Contact list
    string query = "ma"; // Query string
    vector<vector<string>> suggestions = phoneDirectory(contacts, query);
    
    // Print suggestions for each prefix of the query string
    for (int i = 0; i < suggestions.size(); i++) {
        cout << "Suggestions for prefix '" << query.substr(0, i + 1) << "': ";
        for (const string& word : suggestions[i]) {
            cout << word << " ";
        }
        cout << endl;
    }
    return 0;
}









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