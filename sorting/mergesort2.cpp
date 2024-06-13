#include<iostream>
using namespace std;


void merge(int *arr, int s, int e) { // using new array & copy value
  int mid = s+(e-s)/2;
  int len1 = mid-s+1;
  int len2 = e - mid;
  int * first = new int[len1];
  int *second = new int[len2];

  //copying value
  int mainArrIndex = s;
  for(int i=0; i<len1; i++) {
    first[i] = arr[mainArrIndex++];
  }
  mainArrIndex = mid + 1;
  for(int i=0; i<len2; i++) {
    second[i] = arr[mainArrIndex++];
  }
  // merge 2 sorted array
  int index1 = 0;
  int index2 = 0;
  mainArrIndex = s;
  while(index1 < len1 && index2 <len2) {
    if(first[index1] < second[index2]) {
      arr[mainArrIndex++] = first[index1++];
    } else {
      arr[mainArrIndex++] = second[index2++];
    }
  }
  while(index1 < len1) {
    arr[mainArrIndex++] = first[index1++];
  }
  while(index2 < len2) {
    arr[mainArrIndex++] = second[index2++];
  }
}

void mergesort(int *arr, int s, int e) {
  //base case
  if(s>=e) return;
  int mid = s+(e-s)/2;
  mergesort(arr, s, mid);
  mergesort(arr, mid+1, e);
  merge(arr, s, e);
}
int main() {
  int arr[7] = {1, 0, 343, 2, 992, 2034, 3};
  mergesort(arr, 0, 6);
  for(int i: arr) {
    cout << i << ' ';
  }
}