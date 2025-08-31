#include <bits/stdc++.h>
using namespace std;
class NumArray {
    vector<int> nums, segTree;
    int n;
    void buildSegTree(int segTreeIdx, int s, int e) {
        if(s == e) {
            segTree[segTreeIdx] = nums[s];
            return;
        }
        int mid = s + (e-s)/2;
        buildSegTree(2*segTreeIdx+1, s, mid);
        buildSegTree(2*segTreeIdx+2, mid+1, e);
        segTree[segTreeIdx] = segTree[2*segTreeIdx+1] + segTree[2*segTreeIdx+2];
    }
    int getSum(int segTreeIdx, int s, int e, int left, int right) {
        // non-overlapping
        if(right < s || left > e)
            return 0;
        // complete overlapping
        else if(left <= s and right >= e)
            return segTree[segTreeIdx];
        // partial overlapping
        else {
            int mid = s + (e-s)/2;
            int leftSum = getSum(2*segTreeIdx+1, s, mid, left, right);
            int rightSum = getSum(2*segTreeIdx+2, mid+1, e, left, right);
            return leftSum + rightSum;
        }
    }
    void updateSegTree(int segTreeIdx, int s, int e, int index, int diff) {
        if(s > index or e < index) // non-overlapping
            return;
        segTree[segTreeIdx] += diff; // updating val
        // update till leaft node
        if(s != e) {
            int mid = s + (e-s)/2;
            updateSegTree(2*segTreeIdx+1, s, mid, index, diff);
            updateSegTree(2*segTreeIdx+2, mid+1, e, index, diff);
        }
    }
public:
    NumArray(vector<int>& nums) {
        this->nums = nums;
        this->n=nums.size();
        segTree = vector<int> (4*n);
        int segTreeIdx = 0, s = 0, e = this->n-1;
        buildSegTree(segTreeIdx, s, e);
    }
    
    void update(int index, int val) { 
        int diff = val - nums[index];
        nums[index] = val;
        int segTreeIdx = 0, s=0, e = this->n-1;
        updateSegTree(segTreeIdx, s, e, index, diff);
    }
    
    int sumRange(int left, int right) {
        int segTreeIdx=0, s=0, e=this->n-1;
        return getSum(segTreeIdx, s, e, left, right);
    }
};

int main() {
    vector<int> nums = {1, 3, 5};
    NumArray numArray(nums);

    cout << numArray.sumRange(0, 2) << endl; // Output: 9 (1+3+5)
    numArray.update(1, 2);                  // nums = [1,2,5]
    cout << numArray.sumRange(0, 2) << endl; // Output: 8 (1+2+5)

    return 0;
}