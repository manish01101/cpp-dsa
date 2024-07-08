#include "0.hpp"

// approach 1: iterative
Node* reverse(Node* head) {
  Node* prev = nullptr;
  Node* curr = head;
  Node* forward = nullptr;
  while (curr != nullptr) {
    forward = curr->next;
    curr->next = prev;
    prev = curr;
    curr = forward;
  }
  return prev;
}

// approach 2: recursive
void solve(Node*& head, Node* curr, Node* prev) {
  // base case
  if (curr == nullptr) {
    head = prev;
    return;
  }
  Node* forward = curr->next;
  solve(head, forward, curr);
  curr->next = prev;
}
Node* reverseRec(Node* head) {
  Node* curr = head;
  Node* prev = nullptr;
  solve(head, curr, prev);
}

// approach 3: 
Node* reverseRec2(Node* head) {
  // base case
  if(head == nullptr || head->next == nullptr) {
    return head;
  }
  Node* miniHead = reverseRec2(head->next);

  head->next->next = head;
  head->next = nullptr;

  return miniHead;
}