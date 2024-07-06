#include<iostream>
using namespace std;

struct employee {
    int id;
    string name;
    float salary;
};

int main() {
    struct employee one;
    one.id = 5;
    cout << one.id << endl;
}