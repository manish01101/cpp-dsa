

Node* deleteFromBST(Node* root, int val) {
    //base case
    if(root == NULL) return root;

    if(root->data == val) {
        // 0 child
        if(root->left == NULL && root->right == NULL) {
            delete root;
            return NULL:
        }

        // 1 child
        //left child
        if(root->left != NULL && root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        //right child
        if(root->left == NULL && root->left != NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        }

        // 2 child
        if(root->left != NULL && root->right != NULL) {
            int mini = minVal(root->right)->data;
            root->data = mini;
            root->right = deleteFromBST(root->right, mini);
            return root;
        }
    }

    else if(root->data > val) {
        //left part me jao
        root->left = deleteFromBST(root->left, val);
        return root;
    }
    else {
        //right part me jao
        root->right = deleteFromBST(root->right, val);
        return root;
    }
}