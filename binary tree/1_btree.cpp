#include<iostream>
#include<queue>
#include<stack>
#include<map>
#include<set>
using namespace std;

class node{
    public:
        int data;
        node* left;
        node* right;
    
        //constructor
        node(int d){
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

void levelOrderTraversal(node* root){  // bfs
    queue<node*> q;
    q.push(root);
    q.push(NULL); // for level wise separator

    while (!q.empty()){
        node* temp = q.front();
        q.pop();
        if(temp == NULL){ //purana level complete traverse ho chuka hai
            cout << endl;
            if(!q.empty()) // queue still has some child nodes
                q.push(NULL);
        }
        else{
            cout << temp->data << " ";
            if(temp->left)
                q.push(temp->left);
            if(temp->right)
                q.push(temp->right);
        }
    } 
}

void inorder(node* root){
    //base case
    if(root == NULL){
        return;
    }
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}
void preorder(node* root){
    //base case
    if(root == NULL) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}
void postorder(node* root){
    //base case
    if(root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

void buildFromOrder(node* &root){
    queue<node*> q;
    cout << "enter data for root" << endl;
    int data;
    cin >> data;
    root = new node(data);
    q.push(root);

    while (!q.empty()){
        node* temp = q.front();
        q.pop();

        cout << "enter left node for: " << temp->data << endl;
        int leftnodeData;
        cin >> leftnodeData;

        if(leftnodeData != -1){
            temp->left = new node(leftnodeData);
            q.push(temp->left);
        }

        cout << "enter right node for: " << temp->data << endl;
        int rightnodeData;
        cin >> rightnodeData;

        if(rightnodeData != -1){
            temp->right = new node(rightnodeData);
            q.push(temp->right);
        }
    }
    
}
int height(node* root){
    //base case
    if(root == NULL) return 0;
    int left = height(root->left);
    int right = height(root->right);
    int ans = max(left, right) + 1;
    return ans;
}
int diameter(node* root){  //T.C - O(n2)
    if(root == NULL) return 0;
    int op1 = (diameter(root->left));
    int op2 = (diameter(root->right));
    int op3 = height(root->left) + height(root->right);
    int ans = max(op1, max(op2, op3));
    return ans;
}
//opmising above diameter fn
pair<int,int> diameterHei(node* root){ // <dia, height>
    //base case
    if(root == NULL){
        pair<int,int> p = make_pair(0,0);
        return p;
    }
    pair<int,int> left = diameterHei(root->left); 
    pair<int,int> right = diameterHei(root->right);

    int op1 = left.first;
    int op2 = right.first;
    int op3 = left.second + right.second + 1;

    pair<int, int> ans;
    ans.first = max(op1, max(op2, op3)); //diameter
    ans.second = max(left.second, right.second) + 1; //height
    return ans;
}
// t.c = O(n)
int diameterOptimised(node* root){
    return diameterHei(root).first;
}

bool isBalanced(node* root){ //T.C = O(n2)
    //base case
    if(root == NULL) return true;
    
    bool left = isBalanced(root->left);
    bool right = isBalanced(root->right);

    bool diff = abs(height(root->left)-height(root->right)) <= 1;

    if(left && right && diff) return true;
    else return false;
}
//optimising above fn - TC = O(n)
pair<bool, int> isBalancedOpt(node* root){
    //base case
    if(root == NULL){
        pair<bool, int> p = make_pair(true, 0);
        return p;
    }
    pair<bool, int> left = isBalancedOpt(root->left);
    pair<bool, int> right = isBalancedOpt(root->right);

    bool leftAns = left.first;
    bool rightAns = right.first;

    bool diff = abs(left.second-right.second) <= 1;
    
    pair<bool,int> ans;
    ans.second = max(left.second, right.second) + 1;
    
    if(leftAns && rightAns && diff){
        ans.first = true;
    }
    else ans.first = false;
    return ans;
}
bool isBalancedAns(node* root){
    return isBalancedOpt(root).first;
}

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

//sum tree
pair<bool, int> isSumTreeFast(node* root){
    //base case
    if(root == NULL){
        pair<bool,int> p = make_pair(true, 0); //<t/f, sum>
        return p;
    }
    //handling for leaf node
    if(root->left == NULL && root->right == NULL){
        // here have doubt, make_pair(true, root->data);
        pair<bool,int> p = make_pair(true, 0); //<t/f, sum>
        return p;
    }
    pair<bool,int> leftAns = isSumTreeFast(root->left);
    pair<bool,int> rightAns = isSumTreeFast(root->right);

    bool isLeftSumTree= leftAns.first;
    bool isRightSumTree= rightAns.first;

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


// zig zag tree traversal
vector<int> zigzagTraversal(node* root){
    vector<int> result;
    if(root == NULL) return result;
    queue<node*> q;
    q.push(root);
    bool leftToRight = true;
    while (!q.empty()){
        int size = q.size();
        vector<int> ans(size);
        //level process
        for(int i = 0; i<size; i++){
            node* frontNode = q.front();
            q.pop();
            //normal / reverse insert
            int index = leftToRight ? i : size-i-1;
            ans[index] = frontNode->data;

            if(frontNode->left) q.push(frontNode->left);
            if(frontNode->right) q.push(frontNode->right);
        }
        //direction change
        leftToRight = !leftToRight;
        // storing data of each level node
        for(auto i : ans){
            result.push_back(i);
        }
    }
    return result;
}

//boundary traversal of binary tree
void traverseLeft(node* root, vector<int> &ans){
    //base case
    if((root == NULL) || (root->left == NULL && root->right == NULL)) return;

    ans.push_back(root->data);
    if(root->left) traverseLeft(root->left, ans);
    else traverseLeft(root->right, ans);
}
void traverseLeaf(node* root, vector<int> &ans){
    //base case
    if(root == NULL) return;
    if(root->left == NULL && root->right == NULL){
        ans.push_back(root->data);
        return;
    }
    traverseLeaf(root->left, ans);
    traverseLeaf(root->right, ans);
}
void traverseRight(node* root, vector<int> &ans){
    //base case
    if((root == NULL) || (root->left == NULL && root->right == NULL)) return;
    
    if(root->right) traverseRight(root->right, ans);
    else traverseLeft(root->left, ans);

    //wapas aagye
    ans.push_back(root->data);
}
vector<int> boundary(node* root){
    vector<int> ans;
    if(root == NULL) return ans;

    ans.push_back(root->data);

    //left part print / store
    traverseLeft(root->left, ans);
    //traverse leaf nodes
    traverseLeaf(root->right, ans);
    //traverse right part
    traverseRight(root->right, ans);

    return ans;
}


//vertical order tree
vector<int> verticalOrder(node* root){
    map<int, map<int,vector<int>>> nodes;
    queue<pair<node*, pair<int,int>>> q;
    vector<int> ans;

    if(root==NULL) return ans;

    q.push(make_pair(root, make_pair(0,0)));

    while(!q.empty()){
        pair<node*, pair<int, int>> temp = q.front();
        q.pop();
        node* frontNode = temp.first;
        int hd = temp.second.first;
        int lvl = temp.second.second;

        nodes[hd][lvl].push_back(frontNode->data);

        if(frontNode->left){
            q.push(make_pair(frontNode->left, make_pair(hd-1, lvl+1)));
        }
        if(frontNode->right){
            q.push(make_pair(frontNode->right, make_pair(hd+1, lvl+1)));
        }
    }
    for(auto i : nodes) {
        for(auto j:i.second){
            for(auto k:j.second){
                ans.push_back(k);
            }
        }
    }
    return ans;
}



//top view
vector<int> topView(node* root){
    vector<int> ans;
    if(root == NULL) return ans;

    map<int, int> topNode;
    queue<pair<node*,int>> q;

    q.push(make_pair(root, 0));

    while(!q.empty()) {
        pair<node*, int> temp = q.front();
        q.pop();
        node* frontNode = temp.first;
        int hd = temp.second;
        
        //if one value is present for a hd, then
        if(topNode.find(hd) == topNode.end())
            topNode[hd] = frontNode->data;
        
        if(frontNode->left)
            q.push(make_pair(frontNode->left, hd-1));
        if(frontNode->right)
            q.push(make_pair(frontNode->right, hd+1));
    }
    for(auto i:topNode){
        ans.push_back(i.second);
    }
    return ans;
}

//bottom view
vector<int> bottomView(node* root){
    vector<int> ans;
    if(root == NULL) return ans;

    map<int, int> topNode;
    queue<pair<node*,int>> q;

    q.push(make_pair(root, 0));

    while(!q.empty()) {
        pair<node*, int> temp = q.front();
        q.pop();
        node* frontNode = temp.first;
        int hd = temp.second;

        topNode[hd] = frontNode->data;
        
        if(frontNode->left)
            q.push(make_pair(frontNode->left, hd-1));
        if(frontNode->right)
            q.push(make_pair(frontNode->right, hd+1));
    }
    for(auto i : topNode){
        ans.push_back(i.second);
    }
    return ans;
}


//left view of binary tree
void solveLV(node* root, vector<int> &ans, int level){
    //base case
    if(root==NULL) return;

    //we entered into a new level
    if(level == ans.size()) 
        ans.push_back(root->data);
    
    solveLV(root->left, ans, level+1);
    solveLV(root->right, ans, level+1);
}
vector<int> leftView(node* root){
    vector<int> ans;
    solveLV(root, ans, 0);
    return ans;
}

//right view of binary tree
void solve(node* root, vector<int> &ans, int level){
    //base case
    if(root==NULL) return;

    //we entered into a new level
    if(level == ans.size()) 
        ans.push_back(root->data);
    
    solve(root->right, ans, level+1);
    solve(root->left, ans, level+1);
}
vector<int> rightView(node* root){
    vector<int> ans;
    solve(root, ans, 0);
    return ans;
}


int main(){

    node* root = NULL;

    //creating a tree
    // root = buildTree(root);
    // cout << "root->data" << root->data << endl;
    // levelOrderTraversal(root);
    
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

    buildFromOrder(root);
    cout << "reach here" << endl;
    levelOrderTraversal(root);

    return 0;
}