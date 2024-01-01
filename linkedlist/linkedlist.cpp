#include<iostream>
#include<vector>
#include<map>
using namespace std;

class Node{
    public:
    int data;
    Node* next;
    //constructor
    Node(int data){
        this->data=data;
        this->next=NULL;
    }
    // //destructor
    ~Node() {
        int value = this->data;
        //free memory
        if(this->next != NULL) {
            delete next;
            this->next = NULL;
        }
        cout << "memory is free for node with data: " << value << endl;
    }
};
void insertathead(int data, Node* &head){
    //creating new node
    Node* temp = new Node(data);
    temp->next=head;
    head=temp;
}

void insertatpos(int data, int pos, Node* &head) {
    Node* prev = head;
    int i = 1;
    while(i < pos-1) {
        prev = prev->next;
        i++;
    }
    Node* nodetoinsert = new Node(data);
    nodetoinsert->next = prev->next;
    prev->next = nodetoinsert;
}

void print(Node* head) {
    while(head != NULL){
        cout << head->data << "->";
        head = head->next;
    }cout << endl;
}

void deleteNode(int pos, Node* &head) {
    //for 1st node
    if(pos == 1) {
        Node* temp = head;
        head = head->next;
        temp->next = NULL;
        delete temp;
    }
    else {
        Node* curr = head;
        Node* prev = NULL;
        int cnt = 1;
        while(cnt < pos) {
            prev = curr;
            curr = curr->next;
            cnt++;
        }
        prev->next = curr->next;
        curr->next = NULL;
        delete curr;
    }
}
Node* getMiddle(Node* head) {
    // if one node
    if(head == NULL || head->next == NULL) return head;
    // if two node
    if(head->next->next == NULL) return head->next;
    // rest 
    Node* slow = head;
    Node* fast = head->next;
    while(fast != NULL) {
        fast = fast->next;
        if(fast != NULL) {
            fast = fast->next;
        }
        slow = slow->next;
    }
    return slow;
}
Node* kReverse(Node* head, int k) {
    // base case
    if(head == NULL) return head;
    // step 1: reverse 1st k nodes
    Node* prev = NULL;
    Node* curr = head;
    Node* next = NULL;
    int count = 0;
    while(count < k && curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        count++;
    }
    // step 2: handled by recursion
    if(next != NULL) head->next = kReverse(next, k);
    return prev;
}
void makeCircular(Node* &head) {
    Node* temp = head;
    // one node
    if(temp->next == NULL) {
        temp->next = temp;
        return;
    }
    // multiple node
    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = head;
}
bool isCircular(Node* &head) {
    // empty list
    if(head == NULL) return true;
    // single node
    if(head->next == NULL) return false;
    else return false;

    // multiple node
    Node* temp = head->next;
    while(temp != head && temp != NULL) temp = temp->next;
    if(temp == NULL) return false;
    if(temp == head) return true;
}
bool isCircularMap(Node* head) {
    if(head == NULL) {
        return false;
    }
    map<Node*, bool> visited;
    Node* temp = head;
    while (temp != NULL) {
        if(visited[temp] == true) {
            cout << "circular at "<< temp->data << endl;
            return true;
        }
        visited[temp] = true;
        temp = temp->next;
    }
    return false;
}
Node* floydDetectLoop(Node* head) {
    if(head == NULL) {
        return NULL;
    }
    Node* slow = head;
    Node* fast = head;

    while(slow != NULL && fast != NULL) {
        fast = fast->next;
        if(fast != NULL) {
            fast = fast->next;
        }
        slow = slow->next;
        if(slow == fast) {
            // cout << "present at " << slow->data << endl;
            return slow;
        }
    }
    return NULL;
}
bool detectLoopUsingfloyd(Node* head) {
    if(floydDetectLoop(head) != NULL) {
        cout << "present at " << floydDetectLoop(head)->data << endl;
        return true;
    }
    else return false;
}

// starting node of a cycle / loop
Node* getStartingNode(Node* head) {
    if(head == NULL) return NULL;

    Node* intersection = floydDetectLoop(head);
    Node* slow = head;
    while (slow != intersection) {
        slow = slow->next;
        intersection = intersection->next;
    }
    return slow;
}
void removeCycle(Node* head) {
// Node* removeCycle(Node* head) {
    if(head == NULL){
        // return NULL;
        return;
    }
    Node* startofLoop = getStartingNode(head);
    Node* temp = startofLoop;
    while(temp->next != startofLoop) {
        temp = temp->next;
    }
    temp->next = NULL;
    // return head;
}
int main(){
    Node* head = new Node(5);
    insertathead(34, head);
    insertathead(434, head);
    insertatpos(22, 1, head);
    insertatpos(224, 2, head);
    insertatpos(222, 1, head);
    print(head);
    // deleteNode(1, head);
    // print(head);

    // Node* mid = getMiddle(head);
    // cout << mid->data << endl;

    // Node* krev = kReverse(head, 3);
    // print(krev);

    // cout << isCircular(head) << endl;
    // makeCircular(head);
    // cout << isCircular(head) << endl;
    // cout << isCircularMap(head) << endl;
    // makeCircular(head);
    // cout << isCircularMap(head) << endl;

    cout << detectLoopUsingfloyd(head) << endl;
    makeCircular(head);
    cout << detectLoopUsingfloyd(head) << endl;

    // cout << "loop started at " << getStartingNode(head)->data << endl;
    
    removeCycle(head);
    cout << "remove cycle called" << endl;
    cout << detectLoopUsingfloyd(head) << endl;
}