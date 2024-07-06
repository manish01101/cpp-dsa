/*
Exception handling in C++ provides a structured way to handle errors and exceptional conditions that may occur during program execution. It allows you to separate error-handling code from normal code, improving code readability and maintainability.

try:
The try block is used to enclose the code that may throw an exception. It identifies the block of code where an exception might occur.

catch:
The catch block is used to handle exceptions thrown by the try block. It specifies the type of exception that can be caught and contains code to handle the exception.

throw:
The throw statement is used to throw an exception manually. It can be used within the try block to signal that an error or exceptional condition has occurred.

#include <stdexcept>  // Required for standard exceptions

Exceptions are Runtime errors
Try and catch blacks are used for handling exceptions
If exceptions are not handled then program may crash
Exceptions must give a message to the user, giving correct reason on cause of exception
A try block can have Multiple catch blocks
Catch-All can catch all exception
Catch-All must be a last block
If classes in inheritance are used in catch block then child class should come first
*/

// #include <iostream>
// using namespace std;
// int division(int a, int b) {
//     if (b == 0)
//         throw 1;
//     return a / b;
// }
// int main() {
//     int x = 10, y = 0, z;
//     try {
//         z = division(x, y);
//         cout << z << endl;
//     }
//     catch (int e) {
//         cout << "Division by zero " << e << endl;
//     }
//     cout << "Bye" << endl;
// }

// #include <iostream>
// #include <stdexcept>  // Required for standard exceptions
// int main() {
//     try {
//         int a = 10, b = 0;
//         if (b == 0) {
//             throw std::runtime_error("Division by zero");
//         }
//         int result = a / b;
//         std::cout << "Result: " << result << std::endl;
//     } catch (const std::exception& e) {
//         std::cerr << "Exception caught: " << e.what() << std::endl; //prints the exception message
//     }
//     return 0;
// }

/*
Custom Exceptions
You can define custom exception classes by deriving from the std::exception class or its subclasses. This allows you to create specialized exception types tailored to your application's needs.
*/

#include <iostream>
#include <stdexcept>
// Custom exception class for negative numbers
class NegativeNumberException : public std::exception {
    public:
    const char* what() const noexcept override {
        return "Negative number encountered";
    }
};
int main() {
    try {
        int num = -5;
        if (num < 0) {
            throw NegativeNumberException();
        }
        std::cout << "Number: " << num << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
    return 0;
}