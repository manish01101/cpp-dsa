#include<iostream>
#include<vector>
using namespace std;

int fib(int n, vector<int> &dp) {
    // base case
    if(n<=1) return n;

    if(dp[n] != -1) return dp[n];

    dp[n] = fib(n-1, dp) + fib(n-2, dp);
    return dp[n];
}
void topDown(int n) {
    vector<int> dp(n+1);
    for(int i=0; i<=n; i++) {
        dp[i] = -1;
    }
    cout << fib(n, dp) << endl;
}

void bottomUp(int n) {
    // step 1 creating arr
    vector<int> dp(n+1);
    // step 2 - update base case
    dp[0] = 0;
    dp[1] = 1;

    // step 3 - update rest arr using prev
    for(int i=2; i<= n; i++) {
        dp[i] = dp[i-1] + dp[i-2];
    }
    cout << dp[n] << endl;
}
void spaceOptimize(int n) {
    int prev1 = 1; 
    int prev2 = 0;

    if(n==0) cout << prev2 << endl;

    for(int i=2; i<=n; i++) {
        int curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    cout << prev1 << endl;
}

int main() {
    int n;
    cin >> n;
    
    // topDown(n);
    // bottomUp(n);
    spaceOptimize(n);
    return 0;
}