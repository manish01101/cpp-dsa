/*
diamond problem: an ambiguity that arises in multiple inheritance when a class inherits from two or more classes that share a common ancestor
solution:
    1. using virtual inheritance
    2. using scope resulution operator

    virtual inheritance: ensures that only one shared instance of the common base class exists in the final derived class
    key points:
        -> virtual keyword tells the compiler to create a single shared instance of the base class
        -> constructor of the virtual base class is called by the constructor of the "most derived class", not by the intermediate classes.

alternative approach: composition over inheritance
    composition: a class contains objects of other classes as members
    */
#include<iostream>
using namespace std;

class A {
public:
    void do_something() {
        cout << "doing" << endl;
    }
};
class B : virtual public A {};
class C : virtual public A {};
class D : public B, public C {};

int main() {
    D obj;
    obj.do_something();
}