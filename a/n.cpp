#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int N, K;
	cin >> N >> K;

	vector<int> stack(N);

	for (int i = 0; i < N; i++) {
		cin >> stack[i];
	}

	int maxSum = 0;


	for (int i = 0; i <= K; i++) {
		int sum = 0;

		for (int j = 0; j < i; j++) {
			sum += stack[j];
		}

		// Pick (K-i) elements from the bottom of the stack
		for (int j = 0; j < K - i; j++) {
			sum += stack[N - 1 - j];
		}

		maxSum = max(maxSum, sum);
	}

	cout << maxSum << endl;

	return 0;
}
