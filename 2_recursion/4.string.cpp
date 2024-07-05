

#include<iostream>
using namespace std;
// reverse string
void rev(string &str, int i, int j) {
    // base case
    if(i > j) {
        return;
    }
    swap(str[i], str[j]);
    rev(str, i+1, j-1);
}

// check palindrome
bool checkPalindrome(string s, int i, int j) {
    // base case
    if (i > j) {
        return false;
    }
    if(s[i] != s[j]) {
        return false;
    }
    return checkPalindrome(s, ++i, --j);
}

// sort array
void sortArray(int *arr, int n) {
    // base case
    if(n==0 || n==1) {
        return;
    }
    for (int i=0; i<n-1; i++) {
        if(arr[i] > arr[i+1]) {
            swap(arr[i], arr[i+1]);
        }
    }

    sortArray(arr, n-1);
}