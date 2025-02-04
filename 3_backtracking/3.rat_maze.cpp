/*
(i, j)
    safe to move from (i, j) to (k, l)
    -> (k,l) belongs to matrix size
    -> m[k][l] = 1
    -> visited[k][l] = 0

after each move
    visited[k][l] = true
when fn call returns
    visited[k][l] = false (backtrack)

tc: 4^(n*n)
sc: O(n*n)
*/

#include<iostream>
#include<vector>
using namespace std;


bool isSafeToMove(vector<vector<int>>& matrix, int n, int x, int y, vector<vector<bool>>& visited) {
    if ((x >= 0 && x < n) && (y >= 0 && y < n) && matrix[x][y] == 1 && visited[x][y] == 0) {
        return true;
    }
    else {
        return false;
    }
}

void solvefn(vector<vector<int>>& matrix, int n, int x, int y, vector<vector<bool>>& visited, string path, vector<string>& ans) {
    // base case
    if (x == n - 1 && y == n - 1) {
        ans.push_back(path);
        return;
    }
    visited[x][y] = true;
    // now check for move: down, up, left, right
    // for lexicographical order -> process down, left, right, up serial wise so, no need to sort
    // for down
    int newx = x + 1;
    int newy = y;
    if (isSafeToMove(matrix, n, newx, newy, visited)) {
        path.push_back('D');
        solvefn(matrix, n, newx, newy, visited, path, ans);
        path.pop_back(); // backtrack
    }
    // left
    newx = x;
    newy = y - 1;
    if (isSafeToMove(matrix, n, newx, newy, visited)) {
        solvefn(matrix, n, newx, newy, visited, path + 'L', ans);
    }
    // right
    newx = x;
    newy = y + 1;
    if (isSafeToMove(matrix, n, newx, newy, visited)) {
        path.push_back('R');
        solvefn(matrix, n, newx, newy, visited, path, ans);
        path.pop_back(); // backtrack
    }
    // up
    newx = x - 1;
    newy = y;
    if (isSafeToMove(matrix, n, newx, newy, visited)) {
        path.push_back('U');
        solvefn(matrix, n, newx, newy, visited, path, ans);
        path.pop_back(); // backtrack
    }
    visited[x][y] = false; // backtrack
}

vector<string> findallpath(vector<vector<int>>& matrix, int n) {
    vector<string> ans;
    if (matrix[0][0] == 0) {
        return ans;
    }
    int srcx = 0, srcy = 0;

    vector<vector<bool>> visited(n, vector<bool>(n, 0));

    string path = "";

    solvefn(matrix, n, srcx, srcy, visited, path, ans);
    // process down, left, right, up serial wise so, no need to sort
    // sort(ans.begin(), ans.end());
    return ans;
}












bool isSafe(int newx, int newy, vector<vector<bool>>& vis, vector<vector<int>>& arr, int n) {
    if ((newx >= 0 && newx < n) && (newy >= 0 && newy < n) && vis[newx][newy] != 1 && arr[newx][newy] == 1)
        return true;
    else
        return false;
}

void solve(int x, int y, vector<vector<int>>& arr, int n, vector<string>& ans, vector<vector<bool>>& vis, string path) {
    //base case
    if (x == n - 1 && y == n - 1) {
        ans.push_back(path);
        return;
    }
    //4 movement D,L,R,U
    //down
    vis[x][y] = 1;
    if (isSafe(x + 1, y, vis, arr, n)) {
        // vis[x][y] = 1;
        solve(x + 1, y, arr, n, ans, vis, path + 'D');
        // vis[x][y] = 0;
    }
    //left
    if (isSafe(x, y - 1, vis, arr, n)) {
        // vis[x][y] = 1;
        solve(x, y - 1, arr, n, ans, vis, path + 'L');
        // vis[x][y] = 0;
    }
    //right
    if (isSafe(x, y + 1, vis, arr, n)) {
        // vis[x][y] = 1;
        solve(x, y + 1, arr, n, ans, vis, path + 'R');
        // vis[x][y] = 0;
    }
    //up
    if (isSafe(x - 1, y, vis, arr, n)) {
        // vis[x][y] = 1;
        solve(x - 1, y, arr, n, ans, vis, path + 'U');
        // vis[x][y] = 0;
    }
    vis[x][y] = 0;
}


vector<string> searchMaze(vector<vector<int>>& arr, int n) {
    vector<string> ans;
    if (arr[0][0] == 0)
        return ans;
    vector<vector<bool>> visited(n, vector<bool>(n, 0));
    string path = "";
    solve(0, 0, arr, n, ans, visited, path);
    return ans;
}

int main() {
    vector<vector<int>> v = { {1,0,0,0}, {1,1,0,0}, {1,1,0,0}, {0,1,1,1} };
    // int n;cout << "enter n: ";
    // cin >> n;cout<< endl;
    // for(int i=0; i<n; i++) {
    //     for(int j=0; j<n; j++) {
    //         cin >> v[i][j];
    //     }
    // }
    vector<string> str = searchMaze(v, 4);
    for (int i = 0; i < str.size(); i++) {
        cout << str[i] << " ";
    }cout << endl;
}


