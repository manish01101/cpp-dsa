#include<iostream>
#include<queue>
#include<stack>
using namespace std;

int main() {
    stack<int> s;
    queue<int> q;
    bool choice;
    cout << "enter choice 1 to push : ";
    cin >> choice;
    cout << endl;
    while(choice) {
        int n;
        cout << "enter element : " ;
        cin >> n; cout << endl;
        q.push(n);
         cout << "enter choice 1 to push : ";
        cin >> choice;
    }
    cout << "reversing queue : " << endl;
    while(!q.empty()) {
        s.push(q.front());
        q.pop();
    }
    while(!s.empty()) {
        q.push(s.top());
        s.pop();
    }
    cout << "printing reverse queue : " << endl;
    while(!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
}