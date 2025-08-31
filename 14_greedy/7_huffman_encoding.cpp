#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>
#include <memory>
using namespace std;
/*
IN HUFFMAN TREE
left traversal -> 0
right traversal -> 1
*/

struct Node {
	char ch;
	int freq;
	Node* left, * right;

	Node(char ch, int freq, Node* left = nullptr, Node* right = nullptr) : ch(ch), freq(freq), left(left), right(right) { }
};

// Compare function for priority queue
struct Compare {
	bool operator()(Node* l, Node* r) {
		return l->freq > r->freq; // min-heap
	}
};

void buildCodeMap(Node* root, string str, unordered_map<char, string>& codeMap) {
	if (!root) return;
	if (!root->left && !root->right) {
		codeMap[root->ch] = str;
	}
	buildCodeMap(root->left, str + "0", codeMap);
	buildCodeMap(root->right, str + "1", codeMap);
}

string encode(const string& text, unordered_map<char, string>& codeMap) {
	string encoded;
	for (char ch : text)
		encoded += codeMap[ch];
	return encoded;
}

string decode(const string& encodedStr, Node* root) {
	string decoded;
	Node* curr = root;
	for (char bit : encodedStr) {
		if (bit == '0') curr = curr->left;
		else curr = curr->right;

		if (!curr->left && !curr->right) {
			decoded += curr->ch;
			curr = root;
		}
	}
	return decoded;
}

Node* buildHuffmanTree(const string& text) {
	unordered_map<char, int> freq;
	for (char ch : text)
		freq[ch]++;

	priority_queue<Node*, vector<Node*>, Compare> minHeap;
	for (auto& pair : freq) {
		minHeap.push(new Node(pair.first, pair.second));
	}

	while (minHeap.size() > 1) {
		Node* left = minHeap.top(); minHeap.pop();
		Node* right = minHeap.top(); minHeap.pop();
		Node* parent = new Node('\0', left->freq + right->freq, left, right);
		minHeap.push(parent);
	}

	return minHeap.top();
}

void freeTree(Node* node) {
	if (!node) return;
	freeTree(node->left);
	freeTree(node->right);
	delete node;
}

int main() {
	string text = "huffman coding is cool";

	Node* root = buildHuffmanTree(text);

	unordered_map<char, string> codeMap;
	buildCodeMap(root, "", codeMap);

	cout << "Huffman Codes:\n";
	for (auto& pair : codeMap)
		cout << pair.first << ": " << pair.second << "\n";

	string encoded = encode(text, codeMap);
	cout << "\nEncoded: " << encoded << endl;

	string decoded = decode(encoded, root);
	cout << "\nDecoded: " << decoded << endl;

	freeTree(root);
	return 0;
}

/*
class Node {
public:
	int data;
	Node* left;
	Node* right;

	Node(int d) {
		data = d;
		left = nullptr;
		right = nullptr;
	}
};
class cmp {
public:
	bool operator()(Node* a, Node* b) {
		return a->data > b->data;
	}
};

class Solution {
public:
	void traverse(Node* root, vector<string>& ans, string temp) {
		// base case
		if (root->left == nullptr && root->right == nullptr) {
			ans.push_back(temp);
			return;
		}
		traverse(root->left, ans, temp + '0');
		traverse(root->right, ans, temp + '1');
	}

	vector<string> huffmanCodes(string S, vector<int> f, int N) {
		priority_queue<Node*, vector<Node*>, cmp> pq;

		for (int i = 0; i < N; i++) {
			Node* temp = new Node(f[i]);
			pq.push(temp);
		}

		while (pq.size() > 1) {
			Node* left = pq.top();
			pq.pop();
			Node* right = pq.top();
			pq.pop();

			Node* newNode = new Node(left->data + right->data);
			newNode->left = left;
			newNode->right = right;
			pq.push(newNode);
		}
		// now single ele is left-> which is root node
		Node* root = pq.top();
		vector<string> ans;
		string temp = "";
		traverse(root, ans, temp);
		return ans;
	}
};
*/
