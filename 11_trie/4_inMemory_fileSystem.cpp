#include<iostream>
#include<string>
#include<unordered_map>
#include<algorithm>

using namespace std;

class TrieNode {
public:
	string name; // name of file or directory
	bool isFile;
	string content; // content of file, if it is a file
	unordered_map<string, TrieNode*> children; // child nodes(files and directories)

	TrieNode() : isFile(false), name("") { }
	~TrieNode() {
		for (auto child : children) {
			delete child.second;
		}
	}

	// method to insert a node and return last node in the path, also create intermediate dir if needed
	TrieNode* insert(const string& path, bool fileStatus) { // TC = O(no. of dir)
		TrieNode* node = this;
		size_t prevPos = 1;
		size_t currPos = path.find('/', prevPos); // start search fron index prevPos

		while (currPos != string::npos) {
			string part = path.substr(prevPos, currPos - prevPos); // substring from index prevPos with a length of currPos-prevPos
			if (!node->children.count(part)) {
				node->children[part] = new TrieNode(); // child not exist, create it
			}
			node = node->children[part];
			prevPos = currPos + 1;
			currPos = path.find('/', prevPos);
		}
		// handle last part of the path
		string part = path.substr(prevPos); // substring from index prevPos to end
		if (!node->children.count(part)) {
			node->children[part] = new TrieNode();
		}
		node = node->children[part];

		node->isFile = fileStatus;
		if (fileStatus) {
			node->name = part;
		}
		return node;
	}

	// method to search for a node given a path
	TrieNode* search(const string& path) { // TC = O(no. of dir)
		TrieNode* node = this;
		size_t prevPos = 1;
		size_t currPos = path.find('/', prevPos);

		while (currPos != string::npos) {
			string part = path.substr(prevPos, currPos - prevPos);
			if (!node->children.count(part)) {
				return nullptr;
			}
			node = node->children[part];
			prevPos = currPos + 1;
			currPos = path.find('/', prevPos);
		}
		// handle last part of the path
		string part = path.substr(prevPos);
		if (!node->children.count(part)) {
			return nullptr;
		}
		return node->children[part];
	}
};

class FileSystem {
private:
	TrieNode* root;
public:
	FileSystem() {
		root = new TrieNode();
	}
	~FileSystem() {
		delete root;
	}
	vector<string> ls(const string& path) { // TC = O(m + nlogn); m->len of path, n->no. of child (file, subdir)
		vector<string> result;
		TrieNode* node = root->search(path);
		if (!node) {
			return result;
		}
		if (node->isFile) {
			// if it's a file, add the file name to the result list
			result.push_back(node->name);
		}
		else {
			// if it's a dir, add all the child names to the list
			for (auto& child : node->children) {
				result.push_back(child.first);
			}
		}
		sort(result.begin(), result.end()); // sorting list lexicographically
		return result;
	}
	void mkdir(const string& path) {
		root->insert(path, false);
	}
	void addContentToFile(const string& filePath, const string& content) {
		TrieNode* node = root->insert(filePath, true);
		node->content += content;
	}
	string readContentFromFile(const string& filePath) {
		TrieNode* node = root->search(filePath);
		if (node and node->isFile) {
			return node->content;
		}
		return "";
	}
};