#include<iostream>
#include<map>
using namespace std;
class Node {
  public:
  int data;
  Node* next;
  Node(int data) {
    this->data = data;
    this->next = nullptr;
  }
};


/*
remove duplicate in sorted LL

move forward only => curr != curr->next
not move forward:
if curr == curr->next
then  curr->next = curr->next->next
      delete that middle node

*/




// remove dup in sorted ll
Node* uniqueSortedList(Node* head) {
  // empty list
  if (head == nullptr) return nullptr;

  // non empty list
  Node* curr = head;

  while (curr != nullptr) {
    if ((curr->next != nullptr) && curr->data == curr->next->data) {
      Node* temp = curr->next;
      curr->next = curr->next->next;
      delete temp;
    }
    else {
      curr = curr->next;
    }
  }
  return head;
}

// remove dup in unsorted ll
/*
approach 1: tc=O(n2) sc: 1
  use 2-loop
    while(curr != null)
      node* temp = curr->next
        while(temp != null)
          if(curr->data == temp->data)
            delete
          else
            temp = temp->next;
approach 2: tc=nlogn sc: 1
  step 1: sort ll
  step 2: use remove dup in sorted ll
approach 3: tc:(n) sc: (n)
  map<node*, bool> visited
*/
Node* removeDuplicates(Node* head) {
  if (head == nullptr) return head;

  map<int, bool> visited;
  Node* curr = head;

  visited[curr->data] = true;

  while (curr->next != nullptr) {
    if (visited[curr->next->data] == false) {
      visited[curr->next->data] = true;
      curr = curr->next;
    }
    else {
      Node* temp = curr->next;
      curr->next = curr->next->next;
      delete temp;
    }
  }
  return head;
}