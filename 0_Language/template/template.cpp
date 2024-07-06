#include <iostream>
/*
Templates in C++ provide a way to write generic code that can work with any data type. They allow you to create functions and classes that are parameterized by one or more types. Templates enable code reusability and flexibility by allowing the same code to operate on different data types without the need for duplication.


Function templates allow you to define a generic function that can work with any data type. You specify the generic type(s) using template parameters, and the compiler generates the appropriate function instances for each type used.

Class templates allow you to define a generic class that can work with any data type. Similar to function templates, you specify the generic type(s) using template parameters, and the compiler generates the appropriate class instances for each type used.

*/


// Function template to find the maximum of two values
template <typename T>
T max(T a, T b) {
    return (a > b) ? a : b;
}

// Class template for a generic pair
template <typename T, typename U>
class Pair {
    private:
    T first;
    U second;
    
    public:
    Pair(T a, U b) : first(a), second(b) {}
    void display() {
        std::cout << "(" << first << ", " << second << ")"
            << std::endl;
    }
};
