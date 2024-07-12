#include <iostream>
#include <stack>
#include <vector>
using namespace std;

class Solution {
private:
    vector<int>  nextSmallerElement(int* arr, int n) {
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
    vector<int> prevSmallerElement(int* arr, int n) {
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

    int largestRectangleArea(int* heights, int n) {
        // int n = heights.size();

        vector<int> next(n);
        next = nextSmallerElement(heights, n);

        vector<int> prev(n);
        prev = prevSmallerElement(heights, n);

        int area = -50;

        for (int i = 0; i < n; i++) {
            int l = heights[i];
            if (next[i] == -1) {
                next[i] = n;
            }
            int b = next[i] - prev[i] - 1;

            int newArea = l * b;
            area = max(area, newArea);
        }
        return area;
    }
public:
    int maxArea(int M[][4], int n, int m) {
        //compute area for first row
        int area = largestRectangleArea(M[0], m);
        // next row
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < m; j++) {

                //row update: by adding previous row's value
                if (M[i][j] != 0) {
                    M[i][j] = M[i][j] + M[i - 1][j];
                }
                else
                    M[i][j] = 0;
            }
            //entire row is updated now
            area = max(area, largestRectangleArea(M[i], m));
        }
        return area;
    }
};
int main() {
    Solution s;
    int matrix[4][4] = { {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1} };
    cout << s.maxArea(matrix, 4, 4) << endl;

}