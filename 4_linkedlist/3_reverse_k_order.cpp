#include "0.hpp"

/*
approach
reverse first k nodes (iterative way)
head->next = recursion call
return prev
*/

Node* kReverse(Node* head, int k) {
  // base case
  if (head == nullptr) {
    return NULL;
  }
  Node* prev = nullptr;
  Node* curr = head;
  Node* next = nullptr;
  // step 1: for first k nodes
  int cnt = 0;
  while (curr != nullptr && cnt < k) {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
    cnt++;
  }

  // step 2: use rec 
  if (next != nullptr) {
    head->next = kReverse(next, k);
  }

  // step 3: return prev as head
  return prev;
}