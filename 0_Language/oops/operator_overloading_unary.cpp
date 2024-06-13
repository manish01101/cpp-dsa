#include<iostream>
using namespace std;

class Counter {
    private:
    unsigned int count;
    public:
    Counter() : count(0) {} // no args constructor
    Counter(int x) : count(x) {} // one args constructor

    unsigned int get_count() {return count;}
    // UNARY OPERATOR
    Counter operator ++ () { // prefix operator overloading
        return Counter(++count); // return unnamed temp obj
    }
    Counter operator ++ (int) { // here int represent, it should be postfix operator overloading
        return Counter(count++); // return unnamed temp obj
    }
};

int main() {
    Counter c1, c2;
    cout << "initial: " << c1.get_count() << " " << c2.get_count() << endl;
    ++c1;
    c2 = ++c1;
    cout << "initial: " << c1.get_count() << " " << c2.get_count() << endl;
    c2 = c1++;
    cout << "initial: " << c1.get_count() << " " << c2.get_count() << endl;
}


/*
NOTE: dot operator(member access), scope resolution operator, conditional operator,
pointer to member operator(->) = these operator can not be overloaded

only existing operator can be overloaded except the adove.
*/