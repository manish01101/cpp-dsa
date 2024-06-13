#include <iostream>
using namespace std;
// dividing list into sublist till it have one element
// merging that sublist to get sorted list
// backbone of merge sort is merge fn
void merge(int *arr, int s, int e)
{ // using indexes
    int mid = s + (e - s) / 2;
    int left = s;
    int right = mid + 1;
    int *arr2 = new int[e - s + 1];
    int k = s;
    while (left <= mid && right <= e)
    {
        if (arr[left] < arr[right])
            arr2[k++] = arr[left++];
        else
            arr2[k++] = arr[right++];
    }
    while (left <= mid)
        arr2[k++] = arr[left++];
    while (right <= e)
        arr2[k++] = arr[right++];
    for (int i = s; i <= e; i++) {
        arr[i] = arr2[i];
    }
    delete[] arr2;
}
void mergesort(int *arr, int s, int e)
{
    if (s < e)
    {
        int mid = (s + e) / 2;
        mergesort(arr, s, mid);
        mergesort(arr, mid + 1, e);
        merge(arr, s, e);
    }
}

int main()
{
    int arr[9] = {6, 3, 5, 1, 0, 234, 2, 532, 6549};
    mergesort(arr, 0, 8);
    for (int i : arr)
    {
        cout << i << " ";
    }
    cout << endl;
}