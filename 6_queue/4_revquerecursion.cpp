#include<iostream>
#include<queue>
using namespace std;

void revque(queue<int>& q) {

    if (q.empty()) {
        return;
    }
    int num = q.front();
    q.pop();
    revque(q);
    q.push(num);
}

int main() {
    queue<int> q;
    q.push(50);
    q.push(5);
    q.push(7);
    q.push(2);

    revque(q);

    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
}