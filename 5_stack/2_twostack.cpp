#include<iostream>
using namespace std;

class TwoStack {
private:
    int* arr;
    int top1;
    int top2;
    int size;
public:
    //initialize TwoStack - constructor
    TwoStack(int size) {
        this->size = size;
        top1 = -1;
        top2 = size;
        arr = new int[size];
    }
    void push1(int data) {
        if (top2 - top1 > 1) {
            top1++;
            arr[top1] = data;
        }
        else {
            cout << "stack overflow" << endl;
        }
    }
    void push2(int data) {
        if (top2 - top1 > 1) {
            top2--;
            arr[top2] = data;
        }
        else {
            cout << "stack overflow" << endl;
        }
    }
    int pop1() {
        if (top1 >= 0) {
            int ans = arr[top1];
            top1--;
            return ans;
        }
        else {
            return -1;
        }
    }
    int pop2() {
        if (top2 < size) {
            int ans = arr[top2];
            top2++;
            return ans;
        }
        else {
            return -1;
        }
    }
};
int main() {

}