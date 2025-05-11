#include<iostream>
using namespace std;

int main() {
	auto start = chrono::high_resolution_clock::now();
	const int n = 1000000000;
	for (int i = 0; i < n; i++) {

	}
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
	cout << duration.count() << endl;

	start = chrono::high_resolution_clock::now();
	for (int i = 0; i < n; ++i) {

	}
	end = chrono::high_resolution_clock::now();
	duration = chrono::duration_cast<chrono::milliseconds>(end - start);
	cout << duration.count() << endl;
}