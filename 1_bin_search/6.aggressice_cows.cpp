/*
assign cows such that min distance bt any two of them is as large as possible
search space:
    -> min = 0
    -> max = maxi-mini
    mid = (max+min)/2


    possible case(arr[i] >= arr[mid])
        -> store ans
        -> process right part for finding largest ans
    
*/
#include<iostream>
#include<vector>
using namespace std;
bool isPossible(vector<int> &stalls, int k, int mid) {
    int cowCount = 1;
    int lastPos = stalls[0];

    for(int i=0; i<stalls.size(); i++) {
        if(stalls[i]-lastPos >= mid) {
            cowCount++;
            if(cowCount == k) {
                return true;
            }
            lastPos = stalls[i];
        }
    }
    return false;
}
int aggressiveCows(vector<int> & stalls, int k) {
    sort(stalls.begin(), stalls.end());
    int s=0;
    int maxi = -1;
    for(int i=0; i<stalls.size(); i++) {
        maxi = max(maxi, stalls[i]);
    }
    int e=maxi;
    int ans = -1;
    int mid = (s+e)/2;

    while(s<=e) {
        if(isPossible(stalls, k, mid)) {
            ans = mid;
            s = mid + 1;
        }
        else {
            e = mid - 1;
        }
    }
    return ans;
}