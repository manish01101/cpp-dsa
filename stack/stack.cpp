#include <iostream>
using namespace std;

class Stack {
    public:
    //properties
    int *arr;
    int top, size;
    //behaviour
    Stack(int size) {
        this->size = size;
        arr = new int[size];
        top = -1;
    }

    void push(int data) {
        if (size - top > 1) {
            top++;
            arr[top] = data;
        }
        else {
            cout << "stack overflow" << endl;
        }
    }
    void pop() {
        if(top >= 0) {
            top--;
        }
        else {
            cout << "stack underflow" << endl;
        }
    }
    bool isEmpty() {
        if(top == -1) {
            return true;
        }
        else 
            return false;
    }
    int peek() {
        if(top > -1) {
            return arr[top];
        }
        else {
            cout << "stack is empty " ;
            return -1;
        }
    }
};
int main() {
    Stack s(5);
    s.push(44);
    cout << s.peek() << endl;
    s.pop();
    cout << s.peek() << endl;

    return 0;
}