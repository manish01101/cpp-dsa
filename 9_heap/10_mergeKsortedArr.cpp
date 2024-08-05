#include<iostream>
#include<queue>
using namespace std;


class Element {
public:
    int data;
    int i;
    int j;
    Element(int data, int row, int col) {
        this->data = data;
        i = row;
        j = col;
    }
};
class cmp {
public:
    bool operator()(Element* a, Element* b) {
        return a->data > b->data;
    }
};

/*
approach 1:
-> create an arr
-> insert all ele(i.e. n*k) into an array-> tc: o(n*k)
-> sort arr -> tc: o(n*k log(n*k))

approach 2: tc: O(n*k(log k)), sc: O(k) + O(n*k) => O(n*k)
-> make min-heap
-> store first ele of each arr into heap
-> while minHeap not empty
-> store top ele, pop it from minHeap
-> push min-heap top ele in ans arr
-> insert next ele of each arr into heap, if present
*/

vector<int> mergeKArrays(vector<vector<int>> arr, int K) {
    priority_queue<Element*, vector<Element*>, cmp> minHeap;
    // storing first ele of each k arr
    for (int i = 0; i < K; i++) {
        minHeap.push(new Element(arr[i][0], i, 0)); // ele(data, row, col)
    }

    vector<int> ans;
    //step 2: push min-heap top ele in ans arr
    //total ele = n*k - k => n*k => 
    // push to heap take log(k) for k ele
    // tc: O(n*k(log k))
    while (!minHeap.empty()) {
        Element* temp = minHeap.top();
        ans.push_back(temp->data);
        minHeap.pop();

        int currRow = temp->i;
        int currCol = temp->j;
        // check if ele present in an arr
        if (currCol + 1 < arr[currRow].size()) {
            Element* next = new Element(arr[currRow][currCol + 1], currRow, currCol + 1);
            minHeap.push(next);
        }
    }
    return ans;
}