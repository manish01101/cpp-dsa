#include "0.hpp"
/*
approach 1:
    -> find path for n1 & n2
    -> traverse from last and common ele is lca
approach 2:

*/
class Solution { //tc:o(n), sc: o(height)
public:
    node* lca(node* root, int n1, int n2) {
        //base case
        if (root == NULL)
            return NULL;
        if (root->data == n1 || root->data == n2)
            return root;

        node* leftAns = lca(root->left, n1, n2);
        node* rightAns = lca(root->right, n1, n2);

        if (leftAns != NULL && rightAns != NULL)
            return root;
        else if (leftAns != NULL && rightAns == NULL)
            return leftAns;
        else if (leftAns == NULL && rightAns != NULL)
            return rightAns;
        else
            return NULL;
    }
};