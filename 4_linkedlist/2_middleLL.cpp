#include "0.hpp"
/*
approach 1: find len
approach 2: fast pointer
*/

Node* getMiddle(Node* head) {
  if (head == nullptr || head->next == nullptr) {
    return head;
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

Node* getMiddle(Node* head) {
  Node* slow = head;
  Node* fast = head->next;

  while (fast != nullptr && fast->next != nullptr) {
    slow = slow->next;
    fast = fast->next->next;
  }
  return slow;
}