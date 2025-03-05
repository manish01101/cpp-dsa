#include<iostream>
#include<queue>
using namespace std;
/*
approach 1: tc: n*k(log n*k), sc: n*k
-> create vector and store all LL node->data
-> sort vector
-> join all LL
-> replace LL node data with vector data

approach 2:
    -> create minHeap, and push first ele of k linked list
    -> while min heap not empty
    -> store top ele, pop it from minHeap
    -> join LLs using head and tail node
    -> insert next node in minHeap, if present
*/
class ListNode {
public:
    int val;
    ListNode* next;
    ListNode(int val) : val(val), next(nullptr) {}
};
class compare {
public:
    bool operator() (ListNode* a, ListNode* b) {
        return a->val > b->val;
    }
};
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int k = lists.size();
        if (k == 0) { // no list is present
            return nullptr;
        }
        // creation of minHeap
        priority_queue<ListNode*, vector<ListNode*>, compare> minHeap;
        // putting first ele of each k LL
        for (int i = 0; i < k; i++) {
            if (lists[i] != nullptr) {
                minHeap.push(lists[i]);
            }
        }
        ListNode* head = nullptr;
        ListNode* tail = nullptr;

        while (!minHeap.empty()) {
            ListNode* temp = minHeap.top();
            minHeap.pop();
            // check if head is nullptr
            if (head == nullptr) {
                head = temp;
                tail = temp;
            }
            else { // join list node
                tail->next = temp;
                tail = temp;
            }
            // check whether temp's list has node or empty
            if (temp->next != nullptr) {
                minHeap.push(temp->next);
            }
        }
        return head;
    }
};