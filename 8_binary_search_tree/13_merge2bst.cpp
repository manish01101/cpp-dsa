#include "0.hpp"

/*
approach 1
    find inorder of both bst
    merge both inorder arr(inorder is sorted arr)
    make bst from inorder
*/
void inorder(Node* root, vector<int>& in) {
    if (root == nullptr)
        return;
    inorder(root->left, in);
    in.push_back(root->data);
    inorder(root->right, in);
}

vector<int> mergeArrays(vector<int>& a, vector<int>& b) {
    vector<int> ans(a.size() + b.size());
    int i = 0, j = 0;
    int k = 0;
    while (i < a.size() && j < b.size()) {
        if (a[i] < b[j])
            ans[k++] = a[i++];
        else
            ans[k++] = b[j++];
    }
    while (i < a.size())
        ans[k++] = a[i++];
    while (j < b.size())
        ans[k++] = b[j++];
    return ans;
}

Node* inorderToBST(int s, int e, vector<int>& in) {
    //base case
    if (s > e) return nullptr;

    int mid = (s + e) / 2;
    Node* root = new Node(in[mid]);
    root->left = inorderToBST(s, mid - 1, in);
    root->right = inorderToBST(mid + 1, e, in);
    return root;
}
// main fn
Node* mergeBST(Node* root1, Node* root2) {

    // step 1: store inorder
    vector<int> bst1, bst2;
    inorder(root1, bst1);
    inorder(root2, bst2);

    //step 2: merge both sorted arrays
    vector<int> mergedArray = mergeArrays(bst1, bst2);

    //step 3: use merged inorder array to build bst
    int s = 0, e = mergedArray.size() - 1;
    return inorderToBST(s, e, mergedArray);
}










/*
approach 2:
step 1: converting bst to sorted LinkedList
        root1: tc: O(m) sc: O(h1)
        root2: tc: O(n) sc: O(h2)
    sol: convert right subtree into ll
    : root->right = head;
    : root->left = root;
    : head = root
    : convert left subtree into ll

step 2: merge both sorted linkedlist;   tc: O(m+n) sc: O(1)
step 3: convert sorted LL to BST within;   sc: O(h1 + h2)
*/


void convertIntoSortedDLL(Node* root, Node*& head) {
    //base case
    if (root == NULL)
        return;

    convertIntoSortedDLL(root->right, head);

    root->right = head;
    if (head != NULL)
        head->left = root;
    head = root;
    convertIntoSortedDLL(root->left, head);
}

Node* mergeLinkedList(Node* head1, Node* head2) {
    Node* head = NULL;
    Node* tail = NULL;

    while (head1 != NULL && head2 != NULL) {
        if (head1->data < head2->data) {
            if (head == NULL) {
                head = head1;
                tail = head1;
                head1 = head1->right;
            }
            else {//insert at end
                tail->right = head1;
                head1->left = tail;
                tail = head1;
                head1 = head1->right;
            }
        }
        else {
            if (head == NULL) {
                head = head2;
                tail = head2;
                head1 = head2->right;
            }
            else {
                tail->right = head2;
                head2->left = tail;
                tail = head2;
                head2 = head2->right;
            }
        }
    }
    while (head1 != NULL) {
        tail->right = head1;
        head1->left = tail;
        tail = head1;
        head1 = head1->right;
    }
    while (head2 != NULL) {
        tail->right = head2;
        head2->left = tail;
        tail = head2;
        head2 = head2->right;
    }
    return head;
}


int countNodes(Node* head) {
    int cnt = 0;
    Node* temp = head;
    while (temp != NULL) {
        cnt++;
        temp = temp->right;
    }
    return cnt;
}
Node* sortedLLToBST(Node*& head, int n) {
    // base case
    if (n <= 0 || head == NULL)
        return NULL;

    Node* leftSubtree = sortedLLToBST(head, n / 2);

    Node* root = head;
    root->left = leftSubtree;

    head = head->right;

    root->right = sortedLLToBST(head, n - (n / 2) - 1);
    return root;
}


// main function
Node* mergeBST(Node* root1, Node* root2) {

    // step 1: convert BST into sorted DLL in-place
    Node* head1 = NULL;
    convertIntoSortedDLL(root1, head1);
    head1->left = NULL;

    Node* head2 = NULL;
    convertIntoSortedDLL(root2, head2);
    head2->left = NULL;

    // step 2: merge sorted LL
    Node* head = mergeLinkedList(head1, head2);

    //step 3: convert LL to bst
    return sortedLLToBST(head, countNodes(head));
}