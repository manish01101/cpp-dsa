#pragma once
#include "0.hpp"

node* buildTree(node* root) {
    cout << "enter the data: " << endl;
    int data;
    cin >> data;

    if (data == -1) {
        return NULL;
    }

    root = new node(data);

    cout << "enter data for inserting in left of " << data << endl;
    root->left = buildTree(root->left);
    cout << "enter data for inserting in right of " << data << endl;
    root->right = buildTree(root->right);

    return root;
}

void levelOrderTraversal(node* root) {  // bfs
    queue<node*> q;
    q.push(root);
    q.push(NULL); // for level wise separator

    while (!q.empty()) {
        node* temp = q.front();
        q.pop();
        if (temp == NULL) { //purana level complete traverse ho chuka hai
            cout << endl;
            if (!q.empty()) // queue still has some child nodes
                q.push(NULL);
        }
        else {
            cout << temp->data << " ";
            if (temp->left)
                q.push(temp->left);
            if (temp->right)
                q.push(temp->right);
        }
    }
}
void reverseLevelOrderTraversal(node* root) {
    queue<node*> q;
    stack<vector<int>> levels; // Using a stack to store levels in reverse order

    if (root == NULL)
        return;

    q.push(root);

    while (!q.empty()) {
        int size = q.size();
        vector<int> level; // To store nodes at current level

        for (int i = 0; i < size; ++i) {
            node* temp = q.front();
            q.pop();
            level.push_back(temp->data); // Collect nodes at current level

            if (temp->left)
                q.push(temp->left);
            if (temp->right)
                q.push(temp->right);
        }

        levels.push(level); // Store current level in the stack
    }

    // Print nodes level by level in reverse order
    while (!levels.empty()) {
        vector<int> level = levels.top();
        levels.pop();

        for (int i = 0; i < level.size(); ++i) {
            cout << level[i] << " ";
        }
        cout << endl;
    }
}


void inorder(node* root) {
    //base case
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}
void preorder(node* root) {
    //base case
    if (root == NULL) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}
void postorder(node* root) {
    //base case
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

void buildFromOrder(node*& root) {
    queue<node*> q;
    cout << "enter data for root" << endl;
    int data;
    cin >> data;
    root = new node(data);
    q.push(root);

    while (!q.empty()) {
        node* temp = q.front();
        q.pop();

        cout << "enter left node for: " << temp->data << endl;
        int leftnodeData;
        cin >> leftnodeData;

        if (leftnodeData != -1) {
            temp->left = new node(leftnodeData);
            q.push(temp->left);
        }

        cout << "enter right node for: " << temp->data << endl;
        int rightnodeData;
        cin >> rightnodeData;

        if (rightnodeData != -1) {
            temp->right = new node(rightnodeData);
            q.push(temp->right);
        }
    }

}

// count no. of leaf node
void inorderCnt(node* root, int& count) {
    if (root == NULL) return;
    inorderCnt(root->left, count);
    if (root->left == NULL && root->right == NULL) {
        count++;
    }
    inorderCnt(root->right, count);
}
int countLeaf(node* root) {
    int count = 0;
    inorderCnt(root, count);
    return count;
}



int main() {

    node* root = NULL;

    //creating a tree
    root = buildTree(root);
    cout << "root->data" << root->data << endl;
    levelOrderTraversal(root);
    reverseLevelOrderTraversal(root);

    // cout << endl << height(root) << endl;
    // cout << diameterOptimised(root) << endl;

    // // 1 3 7 -1 -1 11 -1 -1 5 17 -1 -1 -1
 //1 2 4 -1 -1 5 -1 -1 3 -1 6 -1 -1
    // //level order
    // cout << "printing the level order travesal "<< endl;
    // levelOrderTraversal(root);

    // cout << endl;
    // inorder(root);
    // cout << endl;
    // preorder(root);
    // cout << endl;
    // postorder(root);

    // buildFromOrder(root);
    // cout << "reach here" << endl;
    // levelOrderTraversal(root);

    return 0;
}