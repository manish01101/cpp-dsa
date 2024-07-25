#include "0.hpp"


/*
approach
-> step 1: create nodeToParent mapping; <node*, node*> by levelorder traversal, TC: O(n)
-> step 2: find target node o(h)
-> step 3; burn tree in min time

    -> make mapping of node visited <Node*, bool>
    -> insert target node in queue
    -> maked visited as true
    -> check for its left, right & parent, if not visited then insert into queue
    -> if any insertion done in queue, increment time
*/
Node* createParentMapping(Node* root, int target, map<Node*, Node*>& nodeToParent) {
    Node* targetNode = nullptr;

    nodeToParent[root] = nullptr;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* front = q.front();
        q.pop();

        if (front->data == target) { // for targetNode
            targetNode = front;
        }
        if (front->left) {
            q.push(front->left); // push to queue
            nodeToParent[front->left] = front; // mapping
        }
        if (front->right) {
            q.push(front->right); // push to queue
            nodeToParent[front->right] = front; // mapping
        }
    }
    return targetNode;
}
int burnTree(Node* targetNode, map<Node*, Node*>& nodeToParent) {
    // make a visited mapping
    map<Node*, bool> visited;
    // make queue, insert targetNode
    queue<Node*> q;
    q.push(targetNode);
    // marked visited as true
    visited[targetNode] = true;

    int time = 0;

    while (!q.empty()) {
        int size = q.size();
        bool isInsertionDoneInQueue = false;
        // loop for process neighbouring node at once to increase time
        for (int i = 0; i < size; i++) {
            Node* front = q.front();
            q.pop();
            // left
            if (front->left && !visited[front->left]) {
                q.push(front->left);
                visited[front->left] = true;
                isInsertionDoneInQueue = true;
            }
            // right
            if (front->right && !visited[front->right]) {
                q.push(front->right);
                visited[front->right] = true;
                isInsertionDoneInQueue = true;
            }
            // parent
            Node* parent = nodeToParent[front];
            if (parent && !visited[parent]) {
                q.push(parent);
                visited[parent] = true;
                isInsertionDoneInQueue = true;
            }
        }
        // if insertion done increment time
        if (isInsertionDoneInQueue == true) {
            time++;
        }
    }
    return time;
}
int minTimeToBurn(Node* root, int target) { // TC: O(nlogn)

    map<Node*, Node*> nodeToParent;
    Node* targetNode = createParentMapping(root, target, nodeToParent);

    int time = burnTree(targetNode, nodeToParent);
    return time;
}