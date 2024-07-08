#pragma once
#include "0.hpp"
/*
approach 1: tc:(n) sc:(n)
  -> create arr
  -> copy LL content in array
  -> check that arr for palindrome

approach 2: tc:(n) sc: 1
 -> find middlw
 -> reverse from middle->next to last node
*/

Node* reverse(Node* head) {
  if (head == nullptr) return head;

  Node* prev = nullptr;
  Node* curr = head;
  Node* next = nullptr;

  while (curr != nullptr) {
    next = curr->next;
    curr->next = prev;

    prev = curr;
    curr = next;
  }
  return prev;
}
Node* findMiddle(Node* head) {
  if (head == nullptr) return head;
  if (head->next == nullptr) return head;

  Node* slow = head;
  Node* fast = head;

  while (fast != nullptr) {
    slow = slow->next;
    fast = fast->next;
    if (fast != nullptr) {
      fast = fast->next;
    }
  }
  return slow;
}

// approach 2
bool palindromeLL(Node* head) {
  if (head->next == nullptr) return true;

  Node* middle = findMiddle(head);
  cout << "middle data: "<< middle->data<< endl;
  cout << "middlenext data: "<< middle->next->data<< endl;
  Node* tempStart = head;
  cout << "head data: " << head->data << endl;
  Node* tempMiddle = reverse(middle);
  cout << "temp midd: "<< tempMiddle->data << endl;
  while(tempMiddle != nullptr) {
    if(tempStart->data != tempMiddle->data) {
      return false;
    }
    tempStart = tempStart->next;
    tempMiddle = tempMiddle->next;
  }
  return true;
}

int main() {
  Node* head = new Node(1);
  Node* a = new Node(2);
  Node* b = new Node(3);
  Node* c = new Node(3);
  Node* d = new Node(2);
  Node* e = new Node(1);
  // Node* d = new Node(5);
  head->next = a;
  a->next = b;
  b->next = c;
  c->next = d;
  d->next = e;
  // d->next = nullptr;

  cout<< palindromeLL(head) << endl;
}