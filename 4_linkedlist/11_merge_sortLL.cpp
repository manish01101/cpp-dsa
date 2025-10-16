#include "0.hpp"

/*
data replacement not allowed
only link change allowed
*/
Node* getMiddle(Node* head) {
  Node* slow = head;
  Node* fast = head->next;

  while (fast != nullptr && fast->next != nullptr) {
    slow = slow->next;
    fast = fast->next->next;
  }
  return slow;
}

Node* merge(Node*& left, Node*& right) {
  if (left == nullptr)
    return right;
  if (right == nullptr)
    return left;
  Node* ans = new Node(-1);
  Node* temp = ans;

  while (left != nullptr && right != nullptr) {
    if (left->data < right->data) {
      temp->next = left;
      temp = left;
      left = left->next;
    }
    else {
      temp->next = right;
      temp = right;
      right = right->next;
    }
  }
  while (left != nullptr) {
    temp->next = left;
    temp = left;
    left = left->next;
  }
  while (right != nullptr) {
    temp->next = right;
    temp = right;
    right = right->next;
  }
  return ans->next;
}

Node* mergeSort(Node* head) {//Time: O(n log n) (split = O(n log n), merge = O(n log n). Space: O(log n) recursion depth.
  // base case
  if (head == nullptr || head->next == nullptr) {
    return head;
  }
  // break linked list into 2 halves
  Node* mid = getMiddle(head);

  Node* left = head;
  Node* right = mid->next;
  mid->next = nullptr;

  // recursive calls to sort both halves
  left = mergeSort(left);
  right = mergeSort(right);

  // merge both left and right halves
  Node* result = merge(left, right);

  return result;
}


class Solution { //iterative bottom-up merge sort, Time: O(n log n), Space: O(1)
public:
  ListNode* sortList(ListNode* head) {
    if (!head || !head->next) return head;

    // Step 1: count length
    ListNode* temp = head;
    int n = 0;
    while (temp) { temp = temp->next; n++; }

    ListNode dummy(0);
    dummy.next = head;

    for (int size = 1; size < n; size <<= 1) {
      ListNode* prev = &dummy;
      ListNode* curr = dummy.next;

      while (curr) {
        // Step 2: split left sublist
        ListNode* left = curr;
        ListNode* right = split(left, size);
        curr = split(right, size); // next pair
        // Step 3: merge and re-link
        prev = merge(left, right, prev);
      }
    }

    return dummy.next;
  }

private:
  // split first size nodes, return next head
  ListNode* split(ListNode* head, int size) {
    while (--size && head) head = head->next;
    if (!head) return nullptr;
    ListNode* second = head->next;
    head->next = nullptr;
    return second;
  }

  // merge two lists and connect to prev, return tail of merged
  ListNode* merge(ListNode* l1, ListNode* l2, ListNode* prev) {
    ListNode* curr = prev;
    while (l1 && l2) {
      if (l1->val < l2->val) {
        curr->next = l1;
        l1 = l1->next;
      }
      else {
        curr->next = l2;
        l2 = l2->next;
      }
      curr = curr->next;
    }
    curr->next = l1 ? l1 : l2;
    while (curr->next) curr = curr->next;
    return curr; // tail of merged list
  }
};
