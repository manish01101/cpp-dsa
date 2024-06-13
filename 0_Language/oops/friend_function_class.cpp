#include<iostream>

using namespace std;

/*
friend fn & class allow external fn or class to access private/protected member of a class while maintaing encapsulation.

friend fn is a fn that is not a member of a class but has access to the private/protected members of the class if it is declared as a friend inside the class. Friend fn are often used for operations that are logically associated with a class but are not part of the class itself

friend class is a class that is granted access to the private/protected members of another class

USE CASES:
1. ENCAPSULATION BREAKING: Friend fn and classes are useful when external entities need access to private/protected members of a class for specific operations "without compromising encapsulation".

2. OPERATOR OVERLOADING: friend fn are commonly used to overload operators for classes where direct access to privated members is required.

3. TESTING: friend fn and classes can facilitate unit testing by allowing test classes or fn to access private members for testing purposes.
*/
class FriendClass; // forward declaration of class

class MyClass {
    private:
        int num;
    public:
        MyClass(int n) : num(n) {}
        friend void displayNum(const MyClass &obj);
        friend class FriendClass;
};

void displayNum(const MyClass &obj) {
    cout << "Val of num: " << obj.num << endl;
}
// friend class
class FriendClass {
    private:
        int n;
    public:
        FriendClass(int n) : n(n) {} // same name also possible
        void displayFriend(const MyClass &obj) {
            cout << "val of friend obj: " << n << "; val of myclass obj: " << obj.num << endl;
        }
};


int main() {
    MyClass obj(10);
    displayNum(obj);

    FriendClass obj_friend(20);
    obj_friend.displayFriend(obj);

}