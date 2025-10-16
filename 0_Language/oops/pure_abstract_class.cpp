/*
In C++, an "interface" is typically implemented as a pure abstract class where all its member functions are pure virtual functions, and it generally does not contain any data members or concrete methods. The purpose of an interface is to define a contract that any implementing class must adhere to by providing implementations for all its pure virtual functions.

abstract vs pure abstract
Implementation:
Abstract classes can have both implemented methods and pure virtual methods. Interfaces (pure abstract classes) only have pure virtual methods.
State:
Abstract classes can have data members (state). Interfaces generally do not have data members.
Constructors:
Abstract classes can have constructors. Interfaces typically do not have constructors (though their pure abstract nature means they cannot be directly instantiated anyway).
Multiple Inheritance:
A class can inherit from only one abstract class, but it can implement multiple interfaces (pure abstract classes) in C++.
*/
class ILogger {
public:
    virtual void logMessage(const std::string& message) = 0;
    virtual void logError(const std::string& error) = 0;
    virtual ~ILogger() = default; // Virtual destructor is good practice
};

class ConsoleLogger : public ILogger {
public:
    void logMessage(const std::string& message) override {
        // Implementation for logging to console
    }
    void logError(const std::string& error) override {
        // Implementation for logging errors to console
    }
};