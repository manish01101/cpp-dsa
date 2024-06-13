#include<iostream>
using namespace std;

class Distance {
    private:
    int feet;
    float inches;
    public:
    Distance() : feet(0), inches(0.0) {} 
    Distance(int ft, float in) : feet(ft), inches(in) {}
    void set_dist() {
        cout << "\nenter feet: "; cin >> feet;
        cout << "\nenter inches: "; cin >> inches;
    }
    void get_dist() {
        cout << "feet: " << feet << ", inches: " << inches << "\n";
    }
    Distance operator + (Distance) const; // add 2 distances
};

Distance Distance::operator + (Distance d2) const {
    int f =  feet + d2.feet;
    float i = inches + d2.inches;
    if(i >= 12.0) {
        i -= 12.0;
        f++;
    }
    return Distance(f, i); // return temp obj
}
/*
NOTE: 
    the args on the left side of the operator is the obj of which the operator is the member
    the obj on the right side of the operator must be furnished as an arg to the operator
    the left operand is accessed directly as the operator is its member
    the right operand is accessed as the function's arg
    In general, an overloaded operator always requires one less arg than its no. of operands and this rule doesn't apply to friend fn.
*/
int main() {
    Distance d1, d3, d4;
    d1.set_dist();
    Distance d2(11, 6.25);
    d3 = d1 +  d2;  // single "+" operator; returned temp obj is stored in d3
    d4 = d1 + d2 + d3;  // multiple "+" operator

    cout << "d1: "; d1.get_dist(); cout << endl;
    cout << "d2: "; d2.get_dist(); cout << endl;
    cout << "d3: "; d3.get_dist(); cout << endl;
    cout << "d4: "; d4.get_dist(); cout << endl;
}