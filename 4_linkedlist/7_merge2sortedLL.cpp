#include<iostream>
#include<map>
using namespace std;
template <typename T>
class Node {
  public:
  T data;
  Node* next;
  Node(T data) {
    this->data = data;
    this->next = nullptr;
  }
};

template <typename T>
Node<T>* solve(Node<T>* first, Node<T>* second) {
  // if only one node present in first list
  if (first->next == nullptr) {
    first->next = second;
    return first;
  }



  Node* <T> curr1 = first;
  Node* <T> next1 = curr1->next;
  Node* <T> curr2 = second;
  Node* <T> next2 = curr2->next;

  while (next1 != nullptr && curr2 != nullptr) {
    if (curr2->data >= curr1->data && curr2->data <= next1->data) {
      curr1->next = curr2;
      next2 = curr2->next;
      curr2->next = next1;

      curr1 = curr2;
      curr2 = next2;
    }
    else {
      curr1 = next1;
      next1 = next1->next;

      if (next1 == nullptr) {
        curr1->next = curr2;
        return first;
      }
    }
  }
  return first;
}

template <typename T>
Node<T>* sortTwoList(Node<T>* first, Node<T>* second) {
  if (first == nullptr)
    return second;
  if (second == nullptr)
    return first;

  if (first->data <= second->data) {
    return solve<T>(first, second);
  }
  else {
    return solve<T>(second, first);
  }
}