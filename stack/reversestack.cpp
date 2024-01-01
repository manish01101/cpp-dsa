#include<iostream>
#include<stack>
using namespace std;


void insertAtBottom(stack<int> &stk, int element) {
    //base case
    if(stk.empty()) {
        stk.push(element);
        return;
    }
    int num = stk.top();
    stk.pop();
    
    //recursive call
    insertAtBottom(stk, element);

    //operation
    stk.push(num);
}
void reverseStack(stack<int> &stk) {
    //base case
    if(stk.empty()) {
        return;
    }

    //operation
    int element = stk.top();
    stk.pop();

    //recursive call
    reverseStack(stk);

    //operation - inserting at bottom
    insertAtBottom(stk, element);
}
int main() {
    stack<int> stk;
    stk.push(7);
    stk.push(1);
    stk.push(4);
    stk.push(5);

    //printing orginal stack
    while(!stk.empty()) {
        cout << stk.top() << endl;
        stk.pop();
    }
    cout << endl;
    //again pushing element
    stk.push(7);
    stk.push(1);
    stk.push(4);
    stk.push(5);

    reverseStack(stk);

    //printing stack
    while(!stk.empty()) {
        cout << stk.top() << endl;
        stk.pop();
    }
    
}