/*interleaving 
    input : 1 2 3 4 5 6 7 8 9 10
   output : 1 6 2 7 3 8 4 9 5 10*/

#include<iostream>
#include<queue>
#include<stack>
using namespace std;

queue<int> ans(queue<int> &q, int size){
    stack<int> s;
    //step 1: first half q -> stack
    for(int i = 0; i<size/2; i++){
        int val = q.front();
        q.pop();
        s.push(val);
    }
    //step 2: s->q
    while(!s.empty()){
        int val = s.top();
        s.pop();
        q.push(val);
    }
    //step 3: first half q => pop & push
    for(int i=0; i<size/2; i++){
        int val = q.front();
        q.pop();
        q.push(val);
    }
    //step 4: first half q -> stack
    for(int i=0; i<size/2; i++){
        int val = q.front();
        q.pop();
        s.push(val);
    }
    //step 5: finally push alternate from s & q
    while(!s.empty()){
        int val = s.top();
        s.pop();
        q.push(val);
        val = q.front();
        q.pop();
        q.push(val);
    }
    return q;
}
int main(){
    queue<int> q;
    int size;
    cout << "size";
    cin >> size;
    for(int i = 0; i<size; i++){
        int n;cin >>n;
        q.push(n);
    }
    ans(q, size);
    for(int i = 0; i<size; i++){
        cout << q.front() << " ";
        q.pop();
    }

}
