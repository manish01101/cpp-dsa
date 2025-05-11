#include<bits/stdc++.h>
using namespace std;
/*
[capture](parameters) -> return_type {
    // body
}
But you usually skip -> return_type unless needed.
*/

// basic lambda
auto greet = []() {
    cout << "Hello, World!" << endl;
};
greet();


// capture list
// by value [=]
int x = 10;
auto show = [=]() {
    cout << "x: " << x << endl;
};
show(); // x: 10

// by Reference [&]
int x = 10;
auto modify = [&]() {
    x += 5;
};
modify();
cout << x << endl; // 15

// with stl
//Sorting with std::sort
vector<int> arr = {4, 2, 7, 1};
sort(arr.begin(), arr.end(), [](int a, int b) {
    return a < b;
});
// Filtering with std::copy_if
vector<int> nums = {1, 2, 3, 4, 5};
vector<int> evens;

copy_if(nums.begin(), nums.end(), back_inserter(evens), [](int n) {
    return n % 2 == 0;
});

// Mutable Lambdas: modify captured variables by value inside the lambda
int a = 10;
auto lambda = [a]() mutable {
    a++;
    cout << a << endl;
};
lambda(); // prints 11
cout << a << endl; // still 10 outside

// Higher Order Functions: Pass lambdas as arguments
void operate(int a, int b, function<int(int, int)> func) {
    cout << "Result: " << func(a, b) << endl;
}

int main() {
    operate(5, 3, [](int x, int y) { return x + y; }); // Result: 8
}

