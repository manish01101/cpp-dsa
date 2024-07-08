#include "0.hpp"
/*
approach 1: find len
approach 2: fast pointer
*/

Node* getMiddle(Node* head) {
  if (head == nullptr || head->next == nullptr) {
    return head;
  }

  // 2 nodes
  if (head->next->next == nullptr) {
    return head->next;
  }

  Node* slow = head;
  Node* fast = head->next;

  while (fast != nullptr) {
    fast = fast->next;
    if (fast != nullptr) {
      fast = fast->next;
    }
    slow = slow->next;
  }
  return slow;
}