#include<iostream>

bool isSorted(int arr[], int i, int size) {
    if(i == size-1){
        return 1;
    }
    if(arr[i] >= arr[i+1]) {
        return 0;
    }
    return isSorted(arr, i+1, size);
}
int firstOcc(int arr[], int i, int size, int key) {
    if(i == size) {
        return -1;
    }
    if(arr[i] == key) {
        return i;
    }
    firstOcc(arr, i+1, size, key);
}

int lastOcc(int arr[], int i, int key) {
    if(i < 0 ) {
        return -1;
    }
    if(arr[i] == key) {
        return i;
    }
    lastOcc(arr, i-1, key);
}
int power(int x, int n) {
    if(n == 1) {
        return x;
    }
    return x * power(x, n-1);
}
//optimised code for power
long long int optiPower(int x, int n) {
    if(n == 1){
        return x;
    }
    long long int aux = optiPower(x, n/2);//t.c O(logn)
    if(n & 1){
        return x*aux*aux;
    }
    else{
        return aux*aux;
    }
}

//tiling problem - covering area
int tilingProblem(int n) {  //floor size = 2 x n
    //base case
    if(n==0 || n==1) {
        return 1;
    }

    // //vertical choice
    // int v = tilingProblem(n-1);
    // //horizontal choice
    // int h = tilingProblem(n-2);
    // int totWays = v + h;
    // return totWays;
    return tilingProblem(n-1) + tilingProblem(n-2);
}

void rmduplicat(std::string &str, int idx, int arr[], std::string &newstr) {
    //base case
    if(idx == str.length()) {
        std::cout << newstr;
    }
    int a = str[idx] - 'a'; //index of arr
    if(arr[a] == 0) {
        newstr.push_back(str[idx]);
        arr[a] = 1;
    }
    //recursive call
    rmduplicat(str, idx+1, arr, newstr);
}

int friendsPairing(int n ) {
    //base case
    if(n == 1 || n == 2) {
        return n;
    }
    return friendsPairing(n-1) + (n-1)*friendsPairing(n-2);
}

void printBinString(int n, int lastplace, std::string str) {
    //base case
    if(n == 0) {
        std::cout << str << std::endl;
        return;
    }
    printBinString(n-1, 0, str+'0');
    if(lastplace==0) {
        printBinString(n-1, 1, str+'1');
    }
}
int main() {
    std::string str;
    printBinString(3, 0, str);

    // std::cout << friendsPairing(4) << std::endl;

    // std::string str = "manishmanish";
    // std::string newstr;
    // int idx = 0;
    // int arr[26] = {0};
    // rmduplicat(str, idx, arr, newstr);

    // std::cout << power(2, 10) << std::endl;
    // std::cout << optiPower(2, 55) << std::endl;
    // std::cout << tilingProblem(4) << std:: endl;
}