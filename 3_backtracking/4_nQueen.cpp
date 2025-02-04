#include<iostream>
#include<vector>
using namespace std;
/*
condition:
each row and col has one queen
no two queen attack each other

tc: n!
sc: n*n
*/
void addSolution(vector<vector<int>>& ans, vector<vector<int>>& board, int n) {
    vector<int> temp;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            temp.push_back(board[i][j]);
        }
    }
    ans.push_back(temp);
}

bool isSafe(int row, int col, vector<vector<int>>& board, int n) {
    int x = row;
    int y = col;
    //check for same row
    while (y >= 0) {
        if (board[x][y] == 1)
            return false;
        y--;
    }
    x = row;
    y = col;
    // check for diagonal
    while (x >= 0 && y >= 0) {
        if (board[x][y] == 1)
            return false;
        y--;
        x--;
    }
    x = row;
    y = col;
    // check for diagonal
    while (x < n && y >= 0) {
        if (board[x][y] == 1)
            return false;
        y--;
        x++;
    }
    return true;
}

void solve(int col, vector<vector<int>>& ans, vector<vector<int>>& board, int n) {
    //base case
    if (col == n) {
        addSolution(ans, board, n);
        return;
    }
    //solve 1 case and recursion will take care
    for (int row = 0; row < n; row++) {
        if (isSafe(row, col, board, n)) {
            //if placing queen is safe
            board[row][col] = 1;
            //recursive call for next col
            solve(col + 1, ans, board, n);
            //backtrack
            board[row][col] = 0;
        }
    }
}

vector<vector<int>> nQueens(int n) {
    vector<vector<int>> board(n, vector<int>(n, 0));
    vector<vector<int>> ans;
    int col = 0;
    solve(col, ans, board, n);
    return ans;
}









class Solution {
private:
    bool isSafe(vector<string>& board, int row, int col, int n) {
        // horizontal
        for (int j = 0; j < n; j++) {
            if (board[row][j] == 'Q') {
                return false;
            }
        }

        // vertical
        for (int i = 0; i < n; i++) {
            if (board[i][col] == 'Q') {
                return false;
            }
        }

        // left diagonal (top-left to bottom-right)
        int i = row, j = col;
        while (i >= 0 && j >= 0) {
            if (board[i][j] == 'Q') {
                return false;
            }
            i--;
            j--;
        }

        // right diagonal (top-right to bottom-left)
        i = row, j = col;
        while (i >= 0 && j < n) {
            if (board[i][j] == 'Q') {
                return false;
            }
            i--;
            j++;
        }

        return true;
    }

    void nQueen(vector<string>& board, int row, int n, vector<vector<string>>& ans) {
        if (row == n) {
            ans.push_back(board);
            return;
        }

        for (int j = 0; j < n; j++) {
            if (isSafe(board, row, j, n)) {
                board[row][j] = 'Q';
                nQueen(board, row + 1, n, ans);
                board[row][j] = '.';  // backtrack
            }
        }
    }

public:
    vector<vector<string>> solveNQueens(int n) {
        vector<string> board(n, string(n, '.'));
        vector<vector<string>> ans;

        nQueen(board, 0, n, ans);
        return ans;
    }
};
