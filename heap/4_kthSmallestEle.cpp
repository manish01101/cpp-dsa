
#include<iostream>
#include<queue>
using namespace std;

int kthSmallest(int arr[], int l, int r, int k) {
    priority_queue<int> pq;

    //step 1
    for(int i=0; i<k; i++) {
        pq.push(arr[i]);
    }
    //step 2
    for(int i=k; i<=r; i++) {
        if(arr[i] < pq.top()) {
            pq.pop();
            pq.push(arr[i]);
        }
    }
    return pq.top();
}

int main() {
    int arr[5] = {7, 10, 4, 20, 15};
    int ans=kthSmallest(arr, 0, 4, 2);
    cout << ans << endl;
}