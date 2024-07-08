#include<iostream>
#include<map>
#include<vector>
#include<algorithm>

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

template <typename T>
class NodeTemplate {
  public:
  T data;
  NodeTemplate* next;

  NodeTemplate(T data) {
    this->data = data;
    this->next = nullptr;
  }
};

Node* reverse(Node* head) {
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