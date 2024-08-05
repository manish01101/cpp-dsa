
#include<iostream>
#include<vector>
#include<queue>
#include<limits.h>
using namespace std;
/*
o/p -> smallest range which contain at least one ele of each k list

approach 3:
-> create minHeap, push first ele of all k arr
-> at the time of inserting, track max ele
-> while minheap not empty
-> check curr range is smaller, if, update ans
*/


class Element {
public:
    int data;
    int row;
    int col;
    Element(int data, int row, int col) : data(data), row(row), col(col) {}
};
class cmp {
public:
    bool operator() (Element* a, Element* b) {
        return a->data > b->data;
    }
};

int kSorted(vector<vector<int>>& a, int k, int n) {
    int mini = INT_MAX, maxi = INT_MIN;
    priority_queue<Element*, vector<Element*>, cmp> minHeap;

    // push k starting ele
    for (int i = 0; i < k; i++) {
        int ele = a[i][0];
        mini = min(mini, ele);
        maxi = max(maxi, ele);
        minHeap.push(new Element(ele, i, 0));
    }

    int start = mini, end = maxi;
    while (!minHeap.empty()) {
        Element* temp = minHeap.top();
        minHeap.pop();
        mini = temp->data;

        if (maxi - mini < end - start) { // check curr range is smaller
            start = mini;
            end = maxi;
        }

        // next ele exist
        if (temp->col + 1 < n) {
            maxi = max(maxi, a[temp->row][temp->col + 1]);
            minHeap.push(new Element(a[temp->row][temp->col + 1], temp->row, temp->col + 1));

        }
        else {
            break;
        }
    }
    return end - start + 1;
}