
/* NOTES:
1. why to use virtual fn?
 -> to achieve dynamic polymorphism which is the ability to call derived class fn using base class pointer/reference
 -> base class pointer to derived class object
*/

#include<iostream>
using namespace std;

class Shape { // abstract class as it only contain pure virtual fn
    public:
    virtual double calculateArea() const = 0;
    virtual void display() const = 0;
};
class Rectangle : public Shape {
    private:
    double length, breadth;

    public:
    Rectangle(double l, double b) : length(l), breadth(b) {}
    double calculateArea() const override {
        return length * breadth;
    }
    void display() const override {
        cout << "area of rec: " << calculateArea() << endl;
    }
};
class Circle : public Shape {
    private:
    double radius;

    public:
    Circle(double r) : radius(r) {}
    double calculateArea() const override {
        return 3.14 * radius * radius;
    }
    void display() const override {
        cout << "area of circle: " << calculateArea() << endl;
    }
};

int main() {
    // method 1
    Shape* shape1;
    Rectangle rec(5.0, 6.0);
    shape1 = &rec;
    shape1->display();

    Circle cir(10);
    shape1 = &cir;
    shape1->display();

    // method 2
    Shape* shape2 = new Circle(10);
    shape2->display();
    delete shape2;
}