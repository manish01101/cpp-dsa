#include<iostream>
using namespace std;

class Test {
  public:
  int a;
  int* p;
  Test(int x) {
    p = new int[x];
  }
  Test(Test& t) {
    a = t.a;
    // p = t.p; 
    p = new int[a];
  }
};


int main() {
  Test t(4);
  for (int i = 0; i < 4; i++) {
    t.p[i] = i;
  }
  for (int i = 0; i < 4; i++) {
    cout << t.p[i];
  } cout << endl;
  Test t2(t);
  for (int i = 0; i < 4; i++) {
    cout << t2.p[i] << " ";
  } cout << endl;
}