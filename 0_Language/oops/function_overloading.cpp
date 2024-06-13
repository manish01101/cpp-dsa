#include<iostream>
using namespace std;
/*
    fn overloading-> done either with different no. of args or different data type of args
*/
void fn() {
    cout << "this is default fn" << endl;
}
void fn(int x) {
    cout << "this is int fn x: " << x << endl;
}
void fn(char c) {
    cout << "this is char fn c: " << c << endl;
}

int main() {
    fn();
    fn(5);
    fn('c');
}