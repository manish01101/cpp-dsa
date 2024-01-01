#include<iostream>
#include<queue>
#include<stack>
using namespace std;

void rev(stack<int> &s, queue<int> &q){
    if(s.empty()){
        return;
    }
    int num = s.top();
    s.pop();
    rev(s, q);
    q.push(num);
}

queue<int> modifyqueue(queue<int> q, int k){
    //algo
    //step 1: pop first k from q and put into stack
    stack<int> s;
    for(int i = 0; i<k; i++){
        s.push(q.front());
        q.pop();
    }

    //step2 put into q
    // rev(s, q);
    while(!s.empty()){
        q.push(s.top());
        s.pop();
    }
    //step 3: fetch first n-k ele from q and push back
    int t = q.size()-k;
    while(t--){
        int val = q.front();
        q.pop();
        q.push(val);
    }

    return q;
}

int main(){
    queue<int> q;
    q.push(50);
    q.push(5);
    q.push(7); 
    q.push(2);
    
    q = modifyqueue(q, 3);

    while(!q.empty()){
        cout << q.front() << " ";
        q.pop();
    }
}