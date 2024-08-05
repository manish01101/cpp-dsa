
#include<iostream>
using namespace std;
/*
heap is completely binary tree that comes with heap order property
cbt: every level is completely filled except last level & nodes always filled from left

max heap: parent's data > child's data
min heap: parent's data < child's data

heap using array
node: i'th index
for 1-based indexing
left child: 2*i'th index
right child: (2*i+1) index

for 0-based indexing
left = 2*i + 1;
right = 2*i + 2;
parent is at (i/2) from its child

insertion in maxheap
step 1: insert node at index = size
step 2: compare with its parent if greater than parent, swap it

deletion in maxheap (deletion of root node)
step 1: swap first node with last node (or arr[1] = arr[last])
step 2: remove last node
step 3: propagate current root node at its current pos
*/

class Heap {
public:
    int arr[100];
    int size = 0;
    Heap() {
        arr[0] = -1;
    }
    void insert(int val) {
        size++;
        int index = size;
        arr[index] = val; // tc: O(1)
        while (index > 1) { // tc: o(logn)
            int parentIndex = index / 2;
            if (arr[parentIndex] < arr[index]) {
                swap(arr[parentIndex], arr[index]);
                index = parentIndex;
            }
            else {
                return;
            }
        }
    }
    void deleteFromHeap() {
        if (size == 0) {
            cout << "Nothing to delete" << endl;
            return;
        }
        arr[1] = arr[size]; // first = last, tc: O(1)
        size--; // decrease size(i.e. remove last)

        // take root node to its correct position tc: O(log n)
        int i = 1;
        while (i < size) {
            int leftIndex = 2 * i;
            int rightIndex = 2 * i + 1;
            if (leftIndex < size && arr[i] < arr[leftIndex]) {
                swap(arr[i], arr[leftIndex]);
                i = leftIndex;
            }
            else if (rightIndex < size && arr[i] < arr[rightIndex]) {
                swap(arr[i], arr[rightIndex]);
                i = rightIndex;
            }
            else {
                return;
            }
        }
    }
    void print() {
        for (int i = 1; i <= size; i++) {
            cout << arr[i] << " ";
        }cout << endl;
    }
};
/*
leaf node is from (n/2 + 1) to n
so for non leaf node i.e from (n/2) to 1 index we have to work on

*/
// maxheap
void heapify(int arr[], int n, int i) {  // tc logn
    int largerstEleIndex = i;
    int leftChildIndex = 2 * i;
    int rightChildIndex = 2 * i + 1;

    if (leftChildIndex < n && arr[largerstEleIndex] < arr[leftChildIndex]) {
        largerstEleIndex = leftChildIndex;
    }
    if (rightChildIndex < n && arr[largerstEleIndex] < arr[rightChildIndex]) {
        largerstEleIndex = rightChildIndex;
    }

    // if largestEleIndex is changed
    if (largerstEleIndex != i) {
        swap(arr[largerstEleIndex], arr[i]);
        heapify(arr, n, largerstEleIndex);
    }
}
void print(int arr[], int n) {
    cout << "printing the array now" << endl;
    for (int i = 1; i <= n; i++) {
        cout << arr[i] << " ";
    }cout << endl;
}
int main() {
    Heap h;
    h.insert(40);
    h.insert(434);
    h.insert(34);
    h.insert(22);
    h.insert(3434);
    h.print();

    int arr[6] = { -1, 54, 53, 55, 52, 50 };
    int n = 5;
    for (int i = n / 2; i > 0; i--)
        heapify(arr, n, i);

    print(arr, n);

    return 0;
}