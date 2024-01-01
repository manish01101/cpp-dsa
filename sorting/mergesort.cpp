#include<iostream>
using namespace std;
//dividing list into sublist till it have one element
//merging that sublist to get sorted list
//backbone of merge sort is merge fn
void merge(int *arr, int s, int e) {
    int i = 0; int j
    while(i <= m && j <= e) {
        if(arr[i] < arr[j])
            arr2[k++] = arr[i++];
        else
            arr2[k++] = arr[j++];
    }
    while(i<=m)
        arr2[k++] = arr[i++];
    while(j<=e)
        arr2[k++] = arr[j++];
    for (i = s; i <= e; i++)
        arr[i] = arr2[i];
}
void mergesort(int *arr, int s, int e){
    if(s < e) {
        int mid = (s+e)/2;
        mergesort(arr, s, mid);
        mergesort(arr, mid+1, e);
        merge(arr, s, e);
    }
}

int main() {
    int arr[5] = {6, 3,5,1, 0};
    mergesort(arr, 0, 4);
    for(int i = 0; i<5; i++){
        cout << arr[i] << " ";
    }cout << endl;
}