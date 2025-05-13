/*
RTTI (Run-Time Type Information)
RTTI allows you to query the type of an object at runtime. It provides mechanisms like dynamic_cast and typeid to determine the actual type of an object and perform type-safe conversions.


Type Casting (static_cast, dynamic_cast, const_cast, reinterpret_cast)
Type casting is the process of converting one type of data to another. C++ provides several casting operators:
• static_cast: Used for implicit conversions that are considered safe by the compiler.
• dynamic_cast: Used for safe downcasting in polymorphic class hierarchies, with runtime type checking.
• const_cast: Used to add or remove const or volatile qualifiers.
• reinterpret_cast: Used for low-level casting between unrelated types, often
considered unsafe.

| Cast Type          | Purpose                                    | Safe?      | Use Case Example                   |
| ------------------ | ------------------------------------------ | ---------- | ---------------------------------- |
| `static_cast`      | Compile-time conversion                    | Safe       | `double → int`, upcasting          |
| `dynamic_cast`     | Runtime-checked downcasting                | Safe       | `Base* → Derived*` in polymorphism |
| `const_cast`       | Add/remove `const` or `volatile` qualifier | Dangerous  | Removing const from parameters     |
| `reinterpret_cast` | Bit-level cast between unrelated types     | Very risky | `int* → char*`, casting addresses  |

*/

#include <iostream>
#include <typeinfo> // for typeid
using namespace std;

class Base {
public:
	virtual void show() {
		cout << "Base class" << endl;
	}
};

class Derived : public Base {
public:
	void show() override {
		cout << "Derived class" << endl;
	}

	void derivedOnly() {
		cout << "Function specific to Derived" << endl;
	}
};

int main() {
	cout << "---- RTTI using typeid ----" << endl;
	Base* b = new Derived();

	cout << "Type of *b: " << typeid(*b).name() << endl; // Outputs type of object being pointed to
	cout << "Type of b: " << typeid(b).name() << endl;   // Outputs type of pointer

	cout << "\n---- dynamic_cast ----" << endl;
	Derived* d1 = dynamic_cast<Derived*>(b); // Safe downcasting
	if (d1) {
		d1->derivedOnly();
	}
	else {
		cout << "dynamic_cast failed" << endl;
	}

	Base* b2 = new Base();
	Derived* d2 = dynamic_cast<Derived*>(b2); // Fails, returns nullptr
	if (d2 == nullptr) {
		cout << "dynamic_cast failed for Base* to Derived*" << endl;
	}

	cout << "\n---- static_cast ----" << endl;
	double pi = 3.14159;
	int int_pi = static_cast<int>(pi); // Truncates decimal part
	cout << "static_cast<double -> int>: " << int_pi << endl;

	Base* basePtr = static_cast<Base*>(d1); // Upcasting: Derived* to Base*
	basePtr->show();

	cout << "\n---- const_cast ----" << endl;
	const int x = 10;
	int& y = const_cast<int&>(x); // Removes const (use with caution!)
	y = 20;
	cout << "After const_cast, x (undefined behavior): " << x << ", y: " << y << endl;

	cout << "\n---- reinterpret_cast ----" << endl;
	int* numPtr = new int(42);
	char* raw = reinterpret_cast<char*>(numPtr); // Treat int pointer as char pointer
	cout << "First byte of int using reinterpret_cast: " << static_cast<int>(*raw) << endl;

	delete b;
	delete b2;
	delete numPtr;

	return 0;
}
