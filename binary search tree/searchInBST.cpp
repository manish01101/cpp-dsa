
//recursive way TC=O(logn) SC = O(n)
bool searchInBST(BinaryTreeNode<int> *root, int x) {
    //base case
    if(root == NULL) return false;

    if(root == x) return true;
    if(root->data > x)
        return searchInBST(root->left, x);
    else
        return searchInBST(root->right, x);
}

//iterative way TC=O(logn) SC = O(1)
bool searchInBST(BinaryTreeNode<int> *root, int x) {

    BinaryTreeNode<int> *temp = root;

    while(temp != NULL) {
        if(temp == x) return true;
        if(temp->data > x) temp=temp->left;
        else temp=temp->right;
    }
    return false;
}

// max 
Node* maxi(BinaryTreeNode<int> *root) {
    Node* temp = root;
    while(temp->right != NULL) temp = temp->right;
    return temp;
}
// min 
Node* mini(BinaryTreeNode<int> *root) {
    Node* temp = root;
    while(temp->left != NULL) temp = temp->left;
    return temp;
}