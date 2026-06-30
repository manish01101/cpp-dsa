#include<iostream>
#include<map>
using namespace std;

map<vector<int>, int> dp;
int findMin(vector<int> arr) {
    if(dp.count(arr)) return dp[arr];

    int n = arr.size();
    int mini = n;

    for(int i=0; i<n-1; i++) {
        int a = arr[i];
        int b = arr[i+1];
        int c = arr[i+2];

        if(2*b == a+c) {
            vector<int> newArr;
            for(int j=0; j<n; j++) {
                if(j!=i and j!=i+1 and j!=i+2) {
                    newArr.push_back(arr[j]);
                }
            }
            int temp = findMin(newArr);
            mini = min(mini, temp);
        }
    }
    dp[arr] = mini;
    return mini;
}
int main() {
    vector<int> arr = {1, 3, 4,5,2,4,5,6,3, 3,4};

    int ans = findMin(arr);
    cout << ans << endl;
}