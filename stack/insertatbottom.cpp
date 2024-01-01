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

    int element = 55;

    insertAtBottom(stk, element);

    //printing stack
    while(!stk.empty()) {
        cout << stk.top() << endl;
        stk.pop();
    }
    
}