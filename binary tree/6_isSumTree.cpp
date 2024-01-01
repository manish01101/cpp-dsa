//sum tree
pair<bool, int> isSumTreeFast(node* root){
    //base case
    if(root == NULL){
        pair<bool,int> p = make_pair(true, 0); //<t/f, sum>
        return p;
    }
    //handling for leaf node
    if(root->left == NULL && root->right == NULL){
        pair<bool,int> p = make_pair(true, 0); //<t/f, sum>
        return p;
    }
    pair<bool,int> leftAns = isSumTreeFast(root->left);
    pair<bool,int> rightAns = isSumTreeFast(root->right);

    bool isLeftSumTree = leftAns.first;
    bool isRightSumTree = rightAns.first;

    bool condition = root->data == (leftAns.second+rightAns.second);

    pair<bool,int> ans;

    if(isLeftSumTree && isRightSumTree && condition){
        ans.first = true;
        ans.second = root->data + leftAns.second + rightAns.second; // 2*root->data
    }
    else{
        ans.first = false;
    }
    return ans;
}
bool isSumTree(node* root){
    return isSumTreeFast(root).first;
}