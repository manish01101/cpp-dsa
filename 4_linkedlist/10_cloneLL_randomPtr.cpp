#include<iostream>
#include<map>
using namespace std;

class Node {
public:
  int data;
  Node* next;
  Node* random;

  Node(int data) {
    this->data = data;
    this->next = nullptr;
    this->random = nullptr;
  }
};

void insertAtTail(Node*& head, Node*& tail, int val) {
  Node* newNode = new Node(val);
  if (head == nullptr) {
    head = newNode;
    tail = newNode;
    return;
  }
  else {
    tail->next = newNode;
    tail = newNode;
  }
}

/*
approach 1: tc:n2
  create a clone list with next pointer
  count distance b/w and point random pointer

approach 2: tc: n, sc: n
  create a clone list using next pointer
  mapping of oldnode with newnode
  map[originalNode->random]  then apply
  cloneNode->random = map[originalNode->random]
*/


// approach 2
Node* copyList(Node* head) {
  // step 1: clone list creation
  Node* cloneHead = nullptr;
  Node* cloneTail = cloneHead;

  Node* temp = head;

  while (temp != nullptr) {
    insertAtTail(cloneHead, cloneTail, temp->data);
    temp = temp->next;
  }
  // step 2: create map
  unordered_map<Node*, Node*> oldToNewNode;
  Node* originalNode = head;
  Node* cloneNode = cloneHead;

  while (originalNode != nullptr && cloneNode != nullptr) {
    oldToNewNode[originalNode] = cloneNode;
    originalNode = originalNode->next;
    cloneNode = cloneNode->next;
  }

  // step 3: setting random pointer
  originalNode = head;
  cloneNode = cloneHead;

  while (originalNode != nullptr) {
    cloneNode->random = oldToNewNode[originalNode->random];
    originalNode = originalNode->next;
    cloneNode = cloneNode->next;
  }
  return cloneHead;
}

/*
approach 3
i. create a clone list
ii. cloneNodes add in between originalList
    head of original list: temp
    temp->next points to starting node of clonedList
iii. copy random pointers
    temp->next->random = temp->random->next
iv. revert changes done in step 2
    originalNode->next = cloneNode->next
*/

Node* copyListOptimised(Node* head) {
  // step 1: create a clone list
  Node* cloneHead = nullptr;
  Node* cloneTail = nullptr;

  Node* temp = head;
  while (temp != nullptr) {
    insertAtTail(cloneHead, cloneTail, temp->data);
    temp = temp->next;
  }
  // step 2: cloneNodes add in between original List
  Node* originalNode = head;
  Node* cloneNode = cloneHead;

  while (originalNode != nullptr && cloneNode != nullptr) {
    Node* next = originalNode->next;
    originalNode->next = cloneNode;
    originalNode = next;

    next = cloneNode->next;
    cloneNode->next = originalNode;
    cloneNode = next;
  }
  // step 3: copy random pointer
  temp = head;
  while (temp != nullptr) {
    if (temp->next != nullptr) {
      temp->next->random = temp->random ? temp->random->next : temp->random;
      // if (temp->random != nullptr) {
      //   temp->next->random = temp->random->next;
      // }
      // else {
      //   temp->next = temp->random;
      // }
    }
    temp = temp->next->next;
  }
  // step 4: revert changes done in step 2
  originalNode = head;
  cloneNode = cloneHead;
  while (originalNode != nullptr && cloneNode != nullptr) {
    originalNode->next = cloneNode->next;
    originalNode = originalNode->next;

    if (originalNode->next != nullptr)
      cloneNode->next = originalNode->next;
    cloneNode = cloneNode->next;
  }
  return cloneHead;
}


class Solution {
  void insertAtTail(Node*& cloneHead, Node*& cloneTail, int data) {
    Node* newNode = new Node(data);
    if (cloneHead == nullptr) {
      cloneHead = newNode;
      cloneTail = newNode;
    }
    else {
      cloneTail->next = newNode;
      cloneTail = newNode;
    }
  }
public:
  Node* copyRandomList(Node* head) {
    if (!head) return nullptr;  // Handle edge case

    // Step 1: Create a clone list
    Node* cloneHead = nullptr;
    Node* cloneTail = nullptr;
    Node* temp = head;
    while (temp != nullptr) {
      insertAtTail(cloneHead, cloneTail, temp->val);
      temp = temp->next;
    }

    // Step 2: Insert cloned nodes between original nodes
    Node* originalNode = head;
    Node* cloneNode = cloneHead;
    while (originalNode != nullptr && cloneNode != nullptr) {
      Node* next = originalNode->next;
      originalNode->next = cloneNode;
      originalNode = next;

      if (originalNode != nullptr) {
        next = cloneNode->next;
        cloneNode->next = originalNode;
        cloneNode = next;
      }
    }

    // Step 3: Copy random pointers
    temp = head;
    while (temp != nullptr) {
      if (temp->random != nullptr) {
        temp->next->random = temp->random->next;
      }
      else {
        temp->next->random = nullptr;
      }
      temp = temp->next->next;
    }

    // Step 4: Restore original list and extract clone list
    originalNode = head;
    cloneNode = cloneHead;
    while (originalNode != nullptr) {
      originalNode->next = cloneNode->next;
      originalNode = originalNode->next;

      if (originalNode != nullptr) {
        cloneNode->next = originalNode->next; // Prevent incorrect linking
      }
      else {
        cloneNode->next = nullptr; // Ensure the clone list terminates
      }
      cloneNode = cloneNode->next;
    }

    return cloneHead;
  }
};
