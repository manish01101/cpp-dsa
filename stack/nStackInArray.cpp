#include<iostream>
using namespace std;

class NStack {
    int *arr;
    int *top;
    int *next;
    int n, s;
    int freespot;
    
    public:
    //initialize data structure->constructor
    NStack(int N, int S) {
        n = N; // no. of stack
        s = S; // array size
        arr = new int[s];
        top = new int[n];
        next = new int[s];

        //initializing top
        for(int i = 0; i<n; i++) {
            top[i] = -1;
        }
        //initializing next
        for(int i = 0; i<s; i++) {
            next[i] = i+1;
        }
        //update last index value to -1
        next[s-1] = -1;
        
        //initialize freespot
        freespot = 0;
    }
    
    //pushes 'x' into the m-th stack, returns true if it gets pushed into the stack, and false otherwise.
    bool push(int x, int m) {
        //check for overflow
        if(freespot == -1) {
            return false;
        }

        //find index
        int index = freespot;

        //update freespot
        freespot = next[index];

        //insert element into array
        arr[index] = x;

        //update next
        next[index] = top[m-1];

        //update top
        top[m-1] = index;

        return true; 
    }

    //pop top element from m-th stack. Return -1 if the stack is empty, otherwise returns the popped element.
    int pop(int m) {
        //check underflow
        if(top[m-1] == -1) {
            return -1;
        }
        
        int index = top[m-1];
        top[m-1] = next[index];
        next[index] = freespot;
        freespot = index;
        
        return arr[index];
    }

};

int main() {
    NStack stk(3, 6);
    stk.push(10, 1);
    stk.push(20, 1);
    stk.push(30, 2);
    stk.push(40, 3);

    stk.pop(1);
    stk.pop(2);

}