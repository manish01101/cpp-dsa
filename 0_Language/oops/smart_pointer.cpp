#include<iostream>
#include<memory>
using namespace std;
/*
unique_ptr -> used when ownership of an obj is unique
shared_ptr -> shared ownership
weak_ptr

*/
int main() {
    unique_ptr<int> ptr_name1(new int);
    *ptr_name1 = 20;

    cout << ptr_name1 << endl;
    cout << *ptr_name1 << endl;
    cout << &ptr_name1 << endl;

    shared_ptr<string> ptr_str1 = make_shared<string>("manish");
    cout << endl << ptr_str1 << endl;
    cout << *ptr_str1 << endl;
    cout << &ptr_str1 << endl;
}