#include<iostream>
using namespace std;

class Node {
  public:
    int data;
    Node* next;
    Node(int data) {
      this->data = data;
      this->next = NULL;
    }
};

void print(Node* temp) {
  while(temp != NULL) {
    cout << temp->data << "->";
  }
  return;
}
void create(Node* &head) {
    int data;
    cout << "enter node data: ";
    cin >> data;
    Node* temp = new Node(data);
    temp->next = head;
    head = temp;
}
int main() {
  Node* head = NULL;

  int t; cin >> t;
  while(t!=0) {
    create(head);
    t--;
  }

  cout << "print :\n";
  print(head);
}