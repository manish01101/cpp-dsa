#include<iostream>
#include<vector>
#include<stack>
using namespace std;

vector<int> nextSmallerElement(vector<int>& arr, int n) {
    stack<int> stk;
    stk.push(-1);
    vector<int> ans(n);

    for (int i = n - 1; i >= 0; i--) {
        int curr = arr[i];
        while (stk.top() >= curr) {
            stk.pop();
        }
        //now top < curr
        ans[i] = stk.top();
        stk.push(curr);
    }
    return ans;
}

int main() {
    vector<int> arr = { 2, 1, 4, 3 };
    int n = 4;

    vector<int> arrf = nextSmallerElement(arr, n);

    for (int i = 0; i < n; i++) {
        cout << arrf[i] << " ";
    }
    cout << endl;

}