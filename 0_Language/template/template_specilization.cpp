
/*
Template Specialization
Template specialization allows you to provide custom implementations for specific data types while still using the generic template for others. It enables you to override the default behavior of a template for certain types.
*/

#include<iostream>
// Template for a generic function
template <typename T>
void print(T value) {
    std::cout << value << std::endl;
}
// Template specialization for char*
template <>
void print<const char*>(const char* value) { // for string literal()
    std::cout << "Specialized for string literal: " << value << std::endl;
}
template<>
void print<std::string>(std::string value) {
    std::cout << "Specialized for string object: " << value << std::endl;
}
int main() {
    print(5);  // Output: 5

    //passed as string literal which is const in nature and Stored in: Read-only section of memory.
    print("world"); // Output: Specialized for string literal: world

    // The std::string class copies the characters from the string literal(i.e. "hello") into its own internal, modifiable buffer.
    std::string str = "hello"; 
    print(str);  // Output: Specialized for string object: hello
    return 0;
}