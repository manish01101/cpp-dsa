#include "0.hpp"

// circular or not
bool isCircularList(Node* head) {
  // empty list
  if (head == nullptr) {
    return true;
  }
  Node* temp = head->next;
  while (temp != nullptr && temp != head) {
    temp = temp->next;
  }
  if (temp == head) {
    return true;
  }
  return false;
}

// detect cycle tc:(n) sc:(n)
bool detectLoop(Node* head) {
  if (head == nullptr) {
    return false;
  }
  map<Node*, bool> visited;
  Node* temp = head;
  while (temp != nullptr) {
    // cycle is present
    if (visited[temp] == true) {
      return true;
    }
    visited[temp] = true;
    temp = temp->next;
  }
  return false;
}

// floyd detection tc:(n) sc: 1
Node* floydDetect(Node* head) {
  if (head == nullptr)
    return nullptr;

  Node* slow = head;
  Node* fast = head;

  while (slow != nullptr && fast != nullptr) {
    slow = slow->next;
    fast = fast->next;
    if (fast != nullptr) {
      fast = fast->next;
    }
    if (slow == fast) {
      return slow;
    }
  }
  return nullptr;
}

// finding starting node of loop
/*
approach 1
step 1: use floyd cycle detection to find point of intersection
step 2: after floyd detection (i.e slow==fast)
  ->slow = head
  ->move slow & fast with same pace(i.e 1)
  ->when slow == fast
    -> this is starting node of loop
*/

Node* getStartingNode(Node* head) {
  if (head == nullptr)
    return head;

  Node* interSectionNode = floydDetect(head);

  if (interSectionNode != nullptr) { // loop present
    Node* slow = head;
    Node* fast = interSectionNode;
    while (slow != fast) {
      slow = slow->next;
      fast = fast->next;
    }
    if (slow == fast) {
      return slow;
    }
  }
  else { // no loop present
    return nullptr;
  }
}

// remove cycle
void removeLoop(Node* head) {
  if (head == nullptr) {
    return;
  }

  Node* startofLoop = getStartingNode(head);
  if (startofLoop == nullptr) {
    return;
  }
  Node* temp = startofLoop;

  while (temp->next != startofLoop) {
    temp = temp->next;
  }
  temp->next = nullptr;
}
