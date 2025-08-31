#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int matrixChainRec(const vector<int>& p, int i, int j) {
    if (i == j) return 0;

    int minCost = INT_MAX;

    for (int k = i; k < j; ++k) {
        int cost = matrixChainRec(p, i, k)
            + matrixChainRec(p, k + 1, j)
            + p[i - 1] * p[k] * p[j];
        minCost = min(minCost, cost);
    }

    return minCost;
}

int matrixChainMemo(int i, int j, const vector<int>& p, vector<vector<int>>& dp) {
    if (i == j) return 0;
    if (dp[i][j] != -1) return dp[i][j];

    int minCost = INT_MAX;

    for (int k = i; k < j; ++k) {
        int cost = matrixChainMemo(i, k, p, dp)
            + matrixChainMemo(k + 1, j, p, dp)
            + p[i - 1] * p[k] * p[j];
        minCost = min(minCost, cost);
    }

    return dp[i][j] = minCost;
}

int matrixChainTabulation(const vector<int>& p) {
    int n = p.size() - 1;
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    for (int l = 2; l <= n; ++l) {          // chain length
        for (int i = 1; i <= n - l + 1; ++i) {
            int j = i + l - 1;
            dp[i][j] = INT_MAX;

            for (int k = i; k < j; ++k) {
                int cost = dp[i][k] + dp[k + 1][j] + p[i - 1] * p[k] * p[j];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }

    return dp[1][n];
}

int main() {
    vector<int> dimensions = { 30, 35, 15, 5, 10 };
    int n = dimensions.size();

    // rec
    cout << "Minimum multiplications (Recursion): " << matrixChainRec(dimensions, 1, n - 1) << endl;

    // rec + mem
    vector<vector<int>> dp(n, vector<int>(n, -1));
    cout << "Minimum multiplications (Rec + Memo): " << matrixChainMemo(1, n - 1, dimensions, dp) << endl;

    // tabulation
    cout << "Minimum multiplications (Tabulation): " << matrixChainTabulation(dimensions) << endl;

    return 0;
}
