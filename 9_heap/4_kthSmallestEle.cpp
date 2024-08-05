
#include<iostream>
#include<queue>
using namespace std;
/*
approach 1: tc: o(nlogn)
if sorted arr => ans = arr[k-1]

approach 2:
by using heap_max
first k ele create a max heap
for rest ele
    if ele < heap.top()
        heap.pop()
        heap.push(ele)
return heap.top()
*/
int kthSmallest(int arr[], int l, int r, int k) {
    priority_queue<int> pq;

    //step 1: push first k ele
    for (int i = 0; i < k; i++) {
        pq.push(arr[i]);
    }
    //step 2: push rest ele
    for (int i = k; i <= r; i++) {
        if (arr[i] < pq.top()) {
            pq.pop();
            pq.push(arr[i]);
        }
    }
    return pq.top();
}


int main() {
    int arr[5] = { 7, 10, 4, 20, 15 };
    int ans = kthSmallest(arr, 0, 4, 2);
    cout << ans << endl;
}
