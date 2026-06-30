#include<bits/stdc++.h>
using namespace std;
/*
A lambda function is an anonymous (unnamed) function you can define inline.
It can be passed as an argument, stored in a variable, or used immediately.

[capture](parameters) -> return_type { body }
capture → Which variables from the surrounding scope to use
parameters → Like normal function parameters
return_type → Optional, usually inferred
body → Function code
*/

// basic lambda
auto greet = []() {
    cout << "Hello, World!" << endl;
};
greet();


// capture Clause ([]): The capture part lets the lambda use variables from the surrounding scope.
int x = 10;
int y = 5;

// Capture by value
auto val = [x, y]() { return x + y; };
cout << val() << endl;  // 15

// Capture by reference
auto ref = [&x, &y]() { x += 1; y += 2; };
ref();
cout << x << " " << y << endl; // 11 7

// Capture everything by value
auto val_all = [=]() { return x + y; };

// Capture everything by reference
auto ref_all = [&]() { x += 1; y += 1; };



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
// By default, a lambda that captures by value cannot modify the captured variable.
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


// Capturing this ->Inside a class, you can capture this to access member variables:
class Counter {
    int x = 0;
public:
    void increment() {
        auto f = [this]() { x++; };
        f();
        cout << x << endl;
    }
};
