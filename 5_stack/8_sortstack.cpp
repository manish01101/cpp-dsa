#include<iostream>
#include<stack>
using namespace std;

void sortedInserting(stack<int>& stk, int element) {
    //base case
    if (stk.empty() || (!stk.empty() && stk.top() < element)) {
        stk.push(element);
        return;
    }
    //operation
    int num = stk.top();
    stk.pop();

    //recursive call
    sortedInserting(stk, element);

    //operation
    stk.push(num);
}

void sortStack(stack<int>& stk) {
    //base case
    if (stk.empty()) {
        return;
    }
    //operation
    int element = stk.top();
    stk.pop();

    //recursive call
    sortStack(stk);

    //operation
    sortedInserting(stk, element);
}
int main() {
    stack<int> stk;
    stk.push(5);
    stk.push(-2);
    stk.push(9);
    stk.push(-7);
    stk.push(3);

    //printing orginal stack
    while (!stk.empty()) {
        cout << stk.top() << endl;
        stk.pop();
    }
    cout << endl;
    stk.push(5);
    stk.push(-2);
    stk.push(9);
    stk.push(-7);
    stk.push(3);

    sortStack(stk);

    //printing orginal stack
    while (!stk.empty()) {
        cout << stk.top() << endl;
        stk.pop();
    }
    return 0;
}