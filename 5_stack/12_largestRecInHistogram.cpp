#include <iostream>
#include <stack>
#include <vector>
using namespace std;

class Solution {
private:
    vector<int> nextSmallerElement(vector<int> arr, int n) {
        stack<int> stk;
        stk.push(-1);
        vector<int> ans(n);

        for (int i = n - 1; i >= 0; i--) {
            int curr = arr[i];
            while (stk.top() != -1 && arr[stk.top()] >= curr) {
                stk.pop();
            }
            // now top < curr
            ans[i] = stk.top();
            stk.push(i);
        }
        return ans;
    }
    vector<int> prevSmallerElement(vector<int> arr, int n) {
        stack<int> stk;
        stk.push(-1);
        vector<int> ans(n);

        for (int i = 0; i < n; i++) {
            int curr = arr[i];
            while (stk.top() != -1 && arr[stk.top()] >= curr) {
                stk.pop();
            }
            // now top < curr
            ans[i] = stk.top();
            stk.push(i);
        }
        return ans;
    }

public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();

        vector<int> next(n);
        next = nextSmallerElement(heights, n);

        vector<int> prev(n);
        prev = prevSmallerElement(heights, n);

        int area = INT32_MIN;

        for (int i = 0; i < n; i++) {
            int l = heights[i];
            // cout << next[i] << " " << prev[i] << " ";
            // for same breadth
            if (next[i] == -1) {
                next[i] = n;
            }
            int b = next[i] - prev[i] - 1;
            // cout << next[i] << " " << prev[i] << " ";
            int newArea = l * b;
            // cout << newArea << endl;
            area = max(area, newArea);
        }
        return area;
    }
};

int main() {
    vector<int> v = { 5, 10, 7 };
    Solution s;
    cout << s.largestRectangleArea(v) << endl;
}