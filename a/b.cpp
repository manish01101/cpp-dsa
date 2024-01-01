#include<iostream>
#include<cmath>
#include<random>
using namespace std;

// void sol(int n) {
//     while(n) {
//         int r = n % 10;
//         cout << r << " ";
//         n /= 10;

//     }
// }



int main() {
    uniform_real_distribution<double> dist(0, 1);
    cout << dist << endl;

    // string s = "d9becfca41ed8d07a394cf422e945eb6c0f87dcc5c07d463be47bdd19546bdfd";
    // cout << s.length() << endl;


    // int arr[8] = {8, 3, 6, 9, 10, 2, 5, 3};

    // cout << firstOcc(arr, 0, 8, 11) << endl;
    // cout << lastOcc(arr, 7, 5) << endl;
    
    // cout << isSorted(arr, 0, 5) << endl;
    
    // int n = 7;
    // for(int i = 0; i < n; i++) {
    //     int ans = pow(11, i);
    //     sol(ans);
    //     cout << endl;
    // }
    return 0;
}