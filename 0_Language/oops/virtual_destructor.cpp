#include <iostream>

class Base {
public:
	Base() { std::cout << "Base constructor\n"; }
	virtual ~Base() { std::cout << "Base destructor\n"; } // Virtual destructor
};

class Derived : public Base {
public:
	Derived() { std::cout << "Derived constructor\n"; }
	~Derived() { std::cout << "Derived destructor\n"; }
};

int main() {
	Base* ptr = new Derived(); // Base pointer to Derived object
	delete ptr; // Calling delete on the base pointer
	return 0;
}

/*
In this example, the virtual keyword in the base class's destructor ensures that the derived class destructor is called when ptr is deleted, even though ptr is of type Base*. Without the virtual destructor, only the Base destructor would have been called, leading to a memory leak in the Derived class
*/