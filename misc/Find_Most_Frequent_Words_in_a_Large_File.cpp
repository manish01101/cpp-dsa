#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

struct WordFreq {
	string word;
	int freq;
	// Reverse comparator for min-heap based on frequency
	bool operator<(const WordFreq& other) const {
		return freq > other.freq; // this makes it a min-heap
	}
};

int main() {
	ifstream file("a.txt");
	if (!file.is_open()) {
		cerr << "Failed to open file\n";
		return 1;
	}

	unordered_map<string, int> wordCnt;
	string line, word;

	while (getline(file, line)) {
		stringstream ss(line);
		while (ss >> word) {
			// Remove punctuation
			word.erase(remove_if(word.begin(), word.end(), [](unsigned char c) {
				return ispunct(c);
				}), word.end());

			// Convert to lowercase
			transform(word.begin(), word.end(), word.begin(), ::tolower);

			if (!word.empty()) {
				wordCnt[word]++;
			}
		}
	}
	file.close();

	const int N = 10;
	priority_queue<WordFreq> minHeap;

	for (const auto& ele : wordCnt) {
		minHeap.push({ ele.first, ele.second });
		if (minHeap.size() > N) {
			minHeap.pop(); // Remove lowest frequency to keep top N
		}
	}

	// Since minHeap has smallest at top, we reverse the result for descending output
	vector<WordFreq> ans;
	while (!minHeap.empty()) {
		ans.push_back(minHeap.top());
		minHeap.pop();
	}
	reverse(ans.begin(), ans.end()); // Optional: to print from highest to lowest

	// Print results
	for (const auto& ele : ans) {
		cout << ele.word << " " << ele.freq << "\n";
	}

	return 0;
}
