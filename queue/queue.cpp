#include<iostream>
// #include<queue>
using namespace std;

// ->initialize 1st element of arr as front and rear 
// ->queue full when rear = n-1
class Queue {
    int* arr;
    int front;
    int rear;
    int size;

    public:
    Queue() {
        size = 10001;
        arr = new int[size];
        front = 0;
        rear = 0;
    }
    //push operation
    void enqueue(int data) {
        if(rear == size)
            cout << "queue is full" << endl;
        else
            arr[ rear++] = data;
    }
    //pop operation
    int dequeue() {
        if(front == rear)
            return -1;
        else {
            int ans = arr[front];
            arr[front++] = -1;
            if(front == rear) // to avoid memory wastage
                front = 0, rear = 0;
            return ans;
        }
    }
    int frontElement() {
        if(front == rear) 
            return -1;
        else
            return arr[front];
    }
    bool isEmpty() {
        if(front == rear)
            return true;
        else 
            return false;
    }
};

int main() {
    Queue q;
    q.enqueue(234);
    cout << q.frontElement() << endl;
    q.dequeue();
    cout << q.frontElement() << endl;

    //creating a queue
    // queue<int> q;
    // q.push(435);
    // q.push(35);
    // q.push(5);

    // cout << q.front() << endl;
    // q.pop();
    // cout << q.front() << endl;
    
    // cout << "size of queue is : "<<q.size() << endl;
    // cout << q.empty() << endl;

    // while (!q.empty())
    // {
    //     cout << q.front() << " ";
    //     q.pop();
    // }
    
}