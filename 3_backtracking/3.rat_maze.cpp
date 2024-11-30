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