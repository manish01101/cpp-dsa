// two identical tree TC = O(n)
bool isIdentical(node* t1, node* t2){
    //base case
    if(t1 == NULL && t2 == NULL) return true;
    if(t1 == NULL && t2 != NULL) return false;
    if(t1 != NULL && t2 == NULL) return false;

    bool left = isIdentical(t1->left, t2->left);
    bool right = isIdentical(t1->right, t2->right);

    bool value = t1->data == t2->data;

    if(left && right && value) return true;
    else return false;
}