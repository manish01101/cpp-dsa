/*
Pointers to members allow storing the addresses of class members (variables or functions) for later use, especially in scenarios like callbacks or event handling.
*/

#include <iostream>
class MyClass {
    public:
    int data = 10;
    void display() {
        std::cout << "Data: " << data << std::endl;
    }
};
int main() {
    int MyClass::* ptr = &MyClass::data; // Pointer to data member
    void (MyClass::* funcPtr)() = &MyClass::display; //Pointer to member function

    MyClass obj;
    std::cout << obj.*ptr << std::endl; // Access data member using pointer
    (obj.*funcPtr)(); // Call member function using pointer

    return 0;
}