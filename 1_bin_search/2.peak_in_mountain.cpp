#include<iostream>
#include<vector>
using namespace std;

int peakIndexMountainArray(vector<int> &arr) {
    int s = 0;
    int e = arr.size() - 1;

    while(s<e) {
        int mid = (s+e )/2;
        if(arr[mid] < arr[mid + 1]) {
            s = mid + 1;
        }
        else {
            e = mid; // not mid-1 as if mid is the peak element then mid-1 point to non-peak element
        }
    }
    return s;
}

