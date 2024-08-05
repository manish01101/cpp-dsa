#include<iostream>
#include<vector>
#include<queue>
using namespace std;
/*
approach 1: insertion sort, o(n2)
-> if new ele is to be added, find its correct pos using bin search tc: o(log n) for pos, + o(n) for rearranging

approach 2: n logn
-> create maxheap and minheap
-> for each ele push to max/min heap based on condition
-> update median
*/
int signum(int a, int b) {
    if (a == b) return 0;
    else if (a > b) return 1;
    else return -1;
}

void callMedian(int element, priority_queue<int>& maxi, priority_queue<int, vector<int>, greater<int> >& mini, int& median) {

    switch (signum(maxi.size(), mini.size())) {
    case 0: // maxheap size == minheap size
        if (element > median) {
            mini.push(element);
            median = mini.top();
        }
        else {
            maxi.push(element);
            median = maxi.top();
        }
        break;
    case 1: // maxheap size > minheap size
        if (element > median) {
            mini.push(element);
            median = (mini.top() + maxi.top()) / 2;
        }
        else {
            mini.push(maxi.top());
            maxi.pop();
            maxi.push(element);
            median = (mini.top() + maxi.top()) / 2;
        }
        break;
    case -1: // maxheap size < minheap size
        if (element > median) {
            maxi.push(mini.top());
            mini.pop();
            mini.push(element);
            median = (mini.top() + maxi.top()) / 2;
        }
        else {
            maxi.push(element);
            median = (mini.top() + maxi.top()) / 2;
        }
        break;
    default:
        break;
    }
}


vector<int> findMedian(vector<int>& arr, int n) {

    vector<int> ans;
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int> > minHeap;
    int median = 0;

    for (int i = 0; i < n; i++) {
        callMedian(arr[i], maxHeap, minHeap, median);
        ans.push_back(median);
    }
    return ans;
}

int main() {
    vector<int> arr = { 1, 2, 3 };
    arr = findMedian(arr, arr.size());
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }cout << "\n";
}