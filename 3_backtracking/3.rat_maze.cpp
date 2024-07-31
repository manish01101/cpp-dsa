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
*/

#include<iostream>
#include<vector>
using namespace std;


// practice by own
bool isSafeToMove(vector<vector<int>>& m, int n, int x, int y, vector<vector<int>> visited) {
    if ((x >= 0 && x < n) && (y >= 0 && y < n) && m[x][y] == 1 && visited[x][y] == 0) {
        return true;
    }
    else {
        return false;
    }
}

void solvefn(vector<vector<int>>& m, int n, int x, int y, vector<vector<int>> visited, string path, vector<string>& ans) {
    // base case
    if (x == n - 1 && y == n - 1) {
        ans.push_back(path);
        return;
    }
    visited[x][y] = true;
    // now check for move: down, up, left, right
    // for down
    int newx = x + 1;
    int newy = y;
    if (isSafeToMove(m, n, newx, newy, visited)) {
        path.push_back('D');
        solvefn(m, n, newx, newy, visited, path, ans);
        path.pop_back(); // backtrack
    }
    // up
    newx = x - 1;
    newy = y;
    if (isSafeToMove(m, n, newx, newy, visited)) {
        path.push_back('U');
        solvefn(m, n, newx, newy, visited, path, ans);
        path.pop_back(); // backtrack
    }
    // left
    newx = x;
    newy = y - 1;
    if (isSafeToMove(m, n, newx, newy, visited)) {
        path.push_back('L');
        solvefn(m, n, newx, newy, visited, path, ans);
        path.pop_back(); // backtrack
    }
    // right
    newx = x;
    newy = y + 1;
    if (isSafeToMove(m, n, newx, newy, visited)) {
        path.push_back('R');
        solvefn(m, n, newx, newy, visited, path, ans);
        path.pop_back(); // backtrack
    }
}

vector<string> findallpath(vector<vector<int>>& m, int n) {
    vector<string> ans;
    if (m[0][0] == 0) {
        return ans;
    }
    int srcx = 0, srcy = 0;

    vector<vector<int>> visited(n, vector<int>(n, 0));

    string path = "";

    solvefn(m, n, srcx, srcy, visited, path, ans);
    sort(ans.begin(), ans.end());
    return ans;
}