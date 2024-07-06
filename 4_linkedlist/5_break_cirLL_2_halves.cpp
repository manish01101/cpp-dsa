#include<iostream>
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


void splitList(Node* head, Node** head1_ref, Node** head2_ref) {
    if (head == NULL || head->next == NULL) {
        return;
    }

    Node* slow = head;
    Node* fast = head->next;

    while (fast->next != head && fast->next->next != head) {
        slow = slow->next;
        fast = fast->next->next;
    }

    if (fast->next->next == head) { // for odd
        fast = fast->next;
        slow = slow->next;
    }

    *head1_ref = head;
    *head2_ref = slow->next;
    slow->next = *head1_ref;
    fast->next = *head2_ref;
}