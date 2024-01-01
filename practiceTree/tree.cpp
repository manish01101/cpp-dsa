#include<iostream>
#include<vector>

using namespace std;

class node {
  public:
    int data;
    node* left;
    node* right;
  // constructor
  node(int d) {
    this->data = d;
    this->left = NULL;
    this->right = NULL;
  }
};
node* buildTree(node* root) {
  cout << "enter the data: " << endl;
  int data;
  cin >> data;

  if(data == -1){
      return NULL;
  }
  root = new node(data);

  cout << "enter data for inserting in left of " << data << endl;
  root->left = buildTree(root->left);
  cout << "enter data for inserting in right of " << data << endl;
  root->right = buildTree(root->right);
  return root;
}
int i = -1;
node* buildPreorder(vector<int> &arr){
  i++;
  if(arr[i] == -1) {
    return NULL;
  } 
  
  node* root = new node(arr[i]);
  root->left = buildPreorder(arr);
  root->right = buildPreorder(arr);
  return root;
}

int main() {
  // node* root = NULL;
  // root = buildTree(root);

  // vector<int> arr = {1,2,4,-1,-1,5,-1,-1,3,-1,6,-1,-1};
  // node* root = buildPreorder(arr);
  // cout << "root->data" << root->data << endl;
  // cout << "root->left->data" << root->left->data<< endl;
  // cout << "root->left->left->data" <<root->left->left->data << endl;
  // cout << "root->left->right->data"<<root->left->right->data << endl;
  // cout << "root->right->data"<<root->right->data << endl;
  // cout << "root->right->left->data"<< root->right->left->data << endl;
  // cout <<" root->right->right->data"<<  root->right->right->data << endl;
}