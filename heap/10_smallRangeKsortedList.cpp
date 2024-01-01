
#include<iostream>
#include<vector>
#include<queue>
#include<limits.h>
using namespace std;

class node {
    public:
    int data;
    int row; 
    int col;
    node(int data, int row, int col) {
        this->data = data;
        this->row = row;
        this->col = col;
    }
};

class compare {
    public:
    bool operator()(node* a, node* b) {
        return a->data > b->data;
    }
};

int kSorted(vector<iint>> &a, int k, int n) {
    int mini = INT_MAX, maxi = INT_MIN;

    priority_queue<node*, vector<node*>, compare> minHeap;

    //step 1: create a min heap for starting ele of each list and tracking mini/maxi value
    for(int i=0; i<k; i++) {
        int ele = a[i][0];
        mini = min(mini, ele);
        maxi = max(maxi, ele);
        minHeap.push(new node(ele, i, 0));
    }
    int start = mini, end = maxi;

    //process ranges
    while(!minHeap.empty()) {
        //mini fetch
        node* temp = minHeap.top();
        minHeap.pop();

        mini = temp->data;
        //range or ans updation
        if(maxi - mini < end - start) {
            start = mini;
            end = maxi;
        }

        if(temp->col + 1 < n) {
            //next ele exist
            maxi = max(maxi, a[temp->row][temp->col + 1]);
            minHeap.push(new node(a[temp->col][temp->col + 1], temp->row, temp->col+1));
        }
        else {break;}//next ele not exist
    }
    return (end - start + 1);
}
