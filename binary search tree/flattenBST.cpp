
void inorder(TreeNode<int>* root, vector<int> &in) {
    if(root == NULL) return;

    inorder(root->left, in);
    in.push_back(root->data);
    inorder(root->right, in);
}

TreeNode<int>* flatten(TreeNode<int>* root) {

    vector<int> inorderVal;
    //store inorder -> sorted values
    inorder(root, inorderVal);
    int n = inorderVal.size();

    //step 1
    TreeNode<int>* newRoot = new TreeNode<int>(inorderVal[0]);
    TreeNode<int>* curr = newRoot;

    //step 2
    for(int i=1; i<n; i++) {
        TreeNode<int>* temp = new TreeNode<int>(inorderVal[i]);
        curr->left = NULL;
        curr->right = temp;
        curr = temp;
    }
    //step 3
    curr->left = NULL;
    curr->right = NULL;
    
    return newRoot;
}