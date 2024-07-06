/* // important ques
sorted & rotated arr 7, 9, 1, 2, 3
pivot ele may be max or min
first part -> 7, 9
second part -> 1, 2, 3
if(arr[mid] >= arr[0]) { // indicates mid is first part only
    start = mid + 1;
}
else {
    e = mid
}
*/
//  HERE WE CHOOSE PIVOT AS MIN
#include<iostream>
using namespace std;

int getPivot(int arr[], int n) {
    int s = 0;
    int e = n - 1;
    while (s < e) {
        int mid = (s + e) / 2;
        if (arr[mid] >= arr[0]) {
            s = mid + 1; // increasing s will get to pivot ele
        }
        else {
            e = mid;
        }
    }
    return s; //or e as both has same value
}

//Question: SEARCH IN SORTED ROTATED ARRAY
/*
arr => 7, 9, 1, 2, 3
step 1: find pivot
step 2: based on pivot divide arr
first part(0 to pivot-1) -> 7, 9
second part(pivot to size) -> 1, 2, 3

if(arr[pivot] <= target <= arr[n-1]) {
    bin search on second part
}
else {
    bin search on first part
    arr[0] <= target <= arr[pivot-1]
}
*/
int binSearch(int arr[], int s, int e, int target) {
    while (s <= e) {
        int mid = (s + e) / 2;
        if (target == arr[mid]) {
            return mid;
        }
        else if (target > arr[mid]) {
            s = mid + 1;
        }
        else {
            e = mid - 1;
        }
    }
    return -1;
}
// final fn
int findIndex(int arr[], int n, int target) {
    int pivot = getPivot(arr, n);
    if (target >= arr[pivot] && target <= arr[n - 1]) { // 2nd part (1, 2, 3)
        return binSearch(arr, pivot, n - 1, target);
    }
    else { // first part (7, 9)
        return binSearch(arr, 0, pivot - 1, target);
    }
}