#include<iostream>
using namespace std;
//stl doubly ended queue
#include<deque>

class Deque {
    int *arr;
    int size;
    int front;
    int rear;
    public:
    //constructor
    Deque(int n) {
        size = n;
        arr = new int[size];
        front = -1;
        rear = -1;
    }
    //push_front
    bool pushFront(int x) {
        //to check whether queue is full
        if((front == 0 && rear == size-1) || (rear == (front-1)%(size-1))) {
            cout << "Queue is full" ;
            return false;
        }
        else if (front == -1) {
            front = rear = 0;
        }
        else if (front == 0 && rear != size - 1) {
            front = size-1;
        }
        else {
            front--;
        }
        arr[front] = x;
        return true;
    }
    bool pushRear(int x) {
        //to check whether queue is full
        if((front == 0 && rear == size-1) || (rear == (front-1)%(size-1))) {
            cout << "Queue is full" ;
            return false;
        }
        else if (front == -1) //first element to push
            front = rear = 0;
        else if (rear == size-1 && front != 0)
            rear = 0; //to maintain cyclic nature
        else
            rear++;  //normal flow
        //push inside the queue
        arr[rear] = x;
        return true;
    }
    int popFront() {
        if(front == -1) { //to check queue is empty
            cout << "queue is empty" << endl;
            return -1;
        }
        int ans = arr[front];
        arr[front] = -1;
        if(front == rear)  // single element is present
            front = rear = -1;
        else if(front == size - 1)
            front = 0;  //to maintain cyclic nature
        else
            front++;
        return ans;
    }
    int popRear() {
        if(front == -1) { //to check queue is empty
            cout << "queue is empty" << endl;
            return -1;
        }
        int ans = arr[rear];
        arr[rear] = -1;
        if(front == rear)  // single element is present
            front = rear = -1;
        else if(rear == 0)
            rear = size - 1; //to maintain cyclic nature
        else
            rear--;
        return ans;
    }
    bool isEmpty() {
        if(front == -1)
            return true;
        else
            return false;
    }
    bool isFull() {
        if((front == 0 && rear == size-1) || (front != 0 && rear == (front-1)%(size-1)))
            return true;
        else
            return false;
    }

    int getFront() {
        if(isEmpty()) {
            return -1;
        }
        return arr[front];
    }
    int getRear() {
        if(isEmpty()) {
            return -1;
        }
        return arr[rear];
    }
};

int main() {
    // deque<int> dq;
    // cout << dq.size() <<endl;
    // dq.push_front(5);
    // dq.push_back(9);
    // cout << dq.front() << endl;
    // cout << dq.back() << endl;
    // cout << dq.size() << endl;
}