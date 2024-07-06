#include<iostream>
using namespace std;

int firstOcc(int arr[], int n, int key) {
    int s = 0, e = n - 1;
    int ans = -1;
    while (s <= e) {
        int mid = s + (e - s) / 2;
        if (arr[mid] == key) {
            ans = mid;
            e = mid - 1;
        }
        else if (arr[mid] < key) {
            s = mid + 1;
        }
        else {
            e = mid - 1;
        }
    }
    return ans;
}
int lastOcc(int arr[], int n, int key) {
    int s = 0, e = n - 1;
    int ans = -1;
    while (s <= e) {
        int mid = s + (e - s) / 2;
        if (arr[mid] == key) {
            ans = mid;
            s = mid + 1;
        }
        else if (arr[mid] < key) {
            s = mid + 1;
        }
        else {
            e = mid - 1;
        }
    }
    return ans;
}
// total no of occ = (lastindex - firstindex) + 1