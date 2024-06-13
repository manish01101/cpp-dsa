#include <iostream>
using namespace std;
// operator overloading practice
class Data {
    public:
    int a;
    Data() : a(0) {}
    Data(int x) : a(x) {}
    Data operator+(Data) const;
};
Data Data::operator+(Data d) const {
    return Data(a + d.a);
}
int main() {
    Data d1(5), d2(6);
    Data d3 = d1 + d2;
    cout << d3.a << endl;
}