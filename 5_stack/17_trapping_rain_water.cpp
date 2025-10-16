class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        vector<int> leftMax(n), rightMax(n);
        leftMax[0]=height[0], rightMax[n-1] = height[n-1];
        for(int i=1; i<n; ++i) {
            leftMax[i] = max(leftMax[i-1], height[i]);
        }
        for(int i=n-2; i>=0; --i) {
            rightMax[i] = max(rightMax[i+1], height[i]);
        }
        int ans = 0;
        for(int i=0; i<n; ++i) {
            int temp = min(leftMax[i], rightMax[i]) - height[i];
            ans += temp;
        }
        return ans;
    }
};
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        int ans = 0;
        int left = 0, right = n-1;
        int leftBoundary = 0, rightBoundary = 0;
        while(left < right) {
            leftBoundary = max(leftBoundary, height[left]);
            rightBoundary = max(rightBoundary, height[right]);
            if(leftBoundary < rightBoundary) {
                ans += leftBoundary-height[left];
                ++left;
            } else {
                ans += rightBoundary-height[right];
                --right;
            }
        }
        return ans;
    }
};
