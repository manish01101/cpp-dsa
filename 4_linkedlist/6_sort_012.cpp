#include "0.hpp"
/*
approach 1:
  -> count times of 0, 1, 2
*/

Node* segregate(Node* head) {
  int zeroCnt = 0, oneCnt = 0, twoCnt = 0;
  Node* temp = head;
  while (temp != NULL) {
    if (temp->data == 0) zeroCnt++;
    else if (temp->data == 1) oneCnt++;
    else if (temp->data == 2) twoCnt++;
    temp = temp->next;
  }
  temp = head;
  while (temp != NULL) {
    if (zeroCnt != 0) {
      temp->data = 0;
      zeroCnt--;
    }
    else if (oneCnt != 0) {
      temp->data = 1;
      oneCnt--;
    }
    else if (twoCnt != 0) {
      temp->data = 2;
      twoCnt--;
    }
    temp = temp->next;
  }
  return head;
}

/*
approach 2: data replacement not allow
so change links
*/
void insertAtTail(Node*& tail, Node* node) {
  tail->next = node;
  tail = node;
}
Node* sortList(Node* head) {
  Node* zeroHead = new Node(-1);
  Node* zeroTail = zeroHead; // for insert at tail
  Node* oneHead = new Node(-1);
  Node* oneTail = oneHead;
  Node* twoHead = new Node(-1);
  Node* twoTail = twoHead;

  Node* curr = head;
  while (curr != NULL) {
    if (curr->data == 0) {
      insertAtTail(zeroTail, curr);
    }
    else if (curr->data == 1) {
      insertAtTail(oneTail, curr);
    }
    else if (curr->data == 2) {
      insertAtTail(twoTail, curr);
    }
    curr = curr->next;
  }

  if (oneHead->next != NULL) {
    zeroTail->next = oneHead->next;
  }
  else {
    zeroTail->next = twoHead->next;
  }
  oneTail->next = twoHead->next;
  twoTail->next = NULL;
  head = zeroHead->next;
  delete zeroHead;
  delete oneHead;
  delete twoHead;
  return head;
}