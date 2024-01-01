#include<iostream>
using namespace std;

class Node {
    public:
        int data;
        Node* prev;
        Node* next;
        //constructor
        Node(int d) {
            this->data = d;
            this->prev = NULL;
            this->next = NULL;
        }
};
void insertatHead(int data, Node* &head) {
    Node* nodetoinsert = new Node(data);
    nodetoinsert->next = head;
    head->prev = nodetoinsert;
    head = nodetoinsert;
}
void insertatTail(int data, Node* &tail) {
    Node* nodetoinsert = new Node(data);
    tail->next = nodetoinsert;
    nodetoinsert->prev = tail;
    tail = nodetoinsert;
}
int getLen(Node* head) {
    int l = 0;
    while (head != NULL) {
        head = head->next;
        l++;
    } return l;
}
void print(Node* head) {
    while (head != NULL) {
        cout << head->data << " -> ";
        head = head->next;
    }cout << endl << endl;
}

int main() {
    Node* begin = new Node(44);
    Node* head = begin;
    Node* tail = begin;
    print(head);
    insertatHead(232, head);
    print(head);
    insertatTail(234, tail);
    insertatTail(234344, tail);

    print(head);
    int l = getLen(head);
    cout << "len: " << l << endl;

}