#include<iostream>
#include<stack>
using namespace std;

void solve(stack <int>& s, int size, int count) {
    //base case
    if (count == size / 2) {
        s.pop();
        return;
    }
    int num = s.top();
    s.pop();

    //recursive call
    solve(s, size, count + 1);

    //operation: adding popped element
    s.push(num);
}

int main() {
    stack <int> s;
    s.push(5);
    s.push(9);
    s.push(12);
    s.push(8);
    s.push(4);

    // while(!s.empty()) {
    //     cout << s.top() << " ";
    //     s.pop();
    // }

    int size = 5;
    int count = 0;
    solve(s, size, count);

    while (!s.empty()) {
        cout << s.top() << endl;
        s.pop();
    }

    return 0;
}