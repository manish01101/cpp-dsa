#include<iostream>
using namespace std;

int main() {
    int* ptr = new int(5); 
    cout << ptr << endl;
    cout << *ptr << endl;
    cout << &ptr << endl;

    *ptr = 10;
    cout << ptr << endl;
    cout << *ptr << endl;
    cout << &ptr << endl;
}