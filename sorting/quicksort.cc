#include<iostream>
using namespace std;
//quicksort based on divide and conquer
//partition is backbone of it
int partition(int *arr, int lb, int ub) {
    int pivot=arr[lb];
    int s = lb, e = ub;
    while(s < e){
        while(arr[s] <= pivot)
            s++;
        while(arr[e] > pivot)
            e--;
        if(s < e)
            swap(arr[s], arr[e]);
    }
    swap(arr[lb], arr[e]);
    return e;
}
void quicksort(int *arr, int s, int e) {
    if(s < e) {
        int pos = partition(arr, s, e);
        quicksort(arr, s, pos-1);
        quicksort(arr, pos+1, e);
    }
}
int main() {
    int arr[5] = {6, 3,5,1, 0};
    quicksort(arr, 0, 4);
    for(int i = 0; i<5; i++){
        cout << arr[i] << " ";
    }cout << endl;
}