#include "0.hpp"


void insertAtTail(Node*& head, Node*& tail, int data) {
  if (head == nullptr) {
    head->data = data;
    return;
  }
  Node* newNode = new Node(data);
  tail->next = newNode;
  tail = newNode;
}

Node* add(Node* first, Node* second) {
  int carry = 0;
  Node* ansHead = nullptr;
  Node* ansTail = ansHead;

  while (first != nullptr && second != nullptr) {
    int sum = carry + first->data + second->data;
    int digit = sum % 10;
    insertAtTail(ansHead, ansTail, digit);
    carry = sum / 10;
    first = first->next;
    second = second->next;
  }
  while (first != nullptr) {
    int sum = carry + first->data;
    int digit = sum % 10;
    insertAtTail(ansHead, ansTail, digit);
    carry = sum / 10;
    first = first->next;
  }
  while (second != nullptr) {
    int sum = carry + second->data;
    int digit = sum % 10;
    insertAtTail(ansHead, ansTail, digit);
    carry = sum / 10;
    second = second->next;
  }
  while (carry != 0) {
    insertAtTail(ansHead, ansTail, carry);
    carry = carry / 10;
  }
  return ansHead;
}

// opmising add fn
Node* addOptimised(Node*& first, Node*& second) {
  int carry = 0;
  Node* ansHead = nullptr;
  Node* ansTail = ansHead;

  while (first != nullptr || second != nullptr || carry != 0) {
    int val1 = 0;
    if (first != nullptr) {
      val1 = first->data;
    }
    int val2 = 0;
    if (second != nullptr) {
      val2 = second->data;
    }

    int sum = carry + val1 + val2;
    int digit = sum % 10;
    insertAtTail(ansHead, ansTail, digit);
    carry = sum / 10;

    // iterate
    if (first != nullptr)
      first = first->next;
    if (second != nullptr)
      second = second->next;
  }
  return ansHead;
}

Node* addTwoLists(Node* first, Node* second) {
  // step 1: reverse ll
  first = reverse(first);
  second = reverse(second);

  // step 2: add ll
  Node* ans = add(first, second);

  // step 3: reverse
  return ans = reverse(ans);
}