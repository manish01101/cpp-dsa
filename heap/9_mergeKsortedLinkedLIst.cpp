#include<iostream>
#include<queue>
using namespace std;

class compare{
    public:
    bool operator()(Node<int> *a, Node<int> *b) {
        return a->data > b->data;
    }
}

Node<int>* mergeKLists(vecor<Node<int>*> &listArray()) {

    priority_queue<Node<int>*, vector<Node<int>*> compare > minHeap;

    int k = listArray.size();
    if(k==0) return NULL;
    //step 1:
    for(int i=0; i<k; i++) {
        if(listArray[i] != NULL) {
            minheap.push();
        }
    }
    while(minHeap.size() > 0) {
        Node<int>* top = minHeap.top();
        minHeap.pop();
        if(top->next != NULL) {
            minHeap.push(top->next);
        }

        if(head == NULL) {
            //ans LL is empty
            head = top;
            tail = top;
        }
        else { //insert at LL
            tail->next = top;
            tail = top;
        }
    }
    return head;
}