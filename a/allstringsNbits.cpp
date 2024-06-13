#include<iostream>
using namespace std;

char arr[5];
void binary(int n) {
  if(n < 1) {
    printf("%s", arr);
    return;
  }
  
  else {
    arr[n-1] = 0;
    binary(n-1);
    arr[n-1] = 1;
    binary(n-1);
  }
}
int main() {
  binary(5);
}