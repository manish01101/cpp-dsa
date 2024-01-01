#include<iostream>
using namespace std;

class Solution{ //tc, sc O(n)
    public:
    node* lca(node* root, int n1, int n2){
        //base case
        if(root == NULL)
            return NULL;
        if(root->data == n1 || root->data == n2)
            return root;

        node* leftAns = lca(root->left, n1, n2);
        node* rightAns = lca(root->right, n1, n2);

        if(leftAns != NULL && right == NULL) 
            return leftAns;
        else if(leftAns != NULL && rightAns == NULL)
            return leftAns;
        else if(leftAns == NULL && rightAns != NULL)
            return rightAns;
        else
            return NULL;
    }
};