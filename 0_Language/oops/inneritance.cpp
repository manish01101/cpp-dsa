/*
INHERITANCE TYPE IN C++
1. SINGLE
2. MULTIPLE
3. MULTILEVEL
4. HIERARCHICAL
5. HYBRID

class Derived : public Base
class Derived : private Base

the keyword public specifies that obj of derived class are able to access public member fn of base class
when private is used, obj of derived class cannot access public member fn of base class => i.e no member of base class is accessible to obj of derived class
Private/protected inheritance does not mean Derived cannot use Base’s members.
It means Derived objects expose none of Base’s members to the outside world.
*/

#include <iostream>
using namespace std;

// 1. Single Inheritance
class Animal {
public:
	void eat() {
		cout << "Animal eats food" << endl;
	}
};
class Dog : public Animal { // Single inheritance
public:
	void bark() {
		cout << "Dog barks" << endl;
	}
};

// 2. Multiple Inheritance
class Walker {
public:
	void walk() {
		cout << "Walker walks" << endl;
	}
};
class Swimmer {
public:
	void swim() {
		cout << "Swimmer swims" << endl;
	}
};
class Amphibian : public Walker, public Swimmer { // Multiple inheritance
public:
	void liveOnLandAndWater() {
		cout << "Amphibian lives on land and water" << endl;
	}
};

// 3. Multilevel Inheritance
class LivingBeing {
public:
	void respire() {
		cout << "LivingBeing breathes" << endl;
	}
};
class Mammal : public LivingBeing {
public:
	void feedMilk() {
		cout << "Mammal feeds milk" << endl;
	}
};
class Human : public Mammal { // Multilevel inheritance
public:
	void speak() {
		cout << "Human speaks" << endl;
	}
};

// 4. Hierarchical Inheritance
class Vehicle {
public:
	void fuel() {
		cout << "Vehicle needs fuel" << endl;
	}
};
class Car : public Vehicle {
public:
	void drive() {
		cout << "Car drives" << endl;
	}
};
class Bike : public Vehicle {
public:
	void ride() {
		cout << "Bike rides" << endl;
	}
};

// 5. Hybrid Inheritance (Combination of Hierarchical + Multiple + Multilevel)
class Engine {
public:
	void start() {
		cout << "Engine starts" << endl;
	}
};
class VehicleBase {
public:
	void fuelType() {
		cout << "Vehicle uses petrol/diesel" << endl;
	}
};
class CarBase : public Engine, public VehicleBase {
public:
	void wheels() {
		cout << "Car has 4 wheels" << endl;
	}
};
class ElectricCar : public CarBase {
public:
	void charge() {
		cout << "ElectricCar charges battery" << endl;
	}
};
