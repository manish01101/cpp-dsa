#include<iostream>
#include<vector>
using namespace std;
/*
condition:
-> each row contains 1-9 exactly once
-> each col contains 1-9 exactly once
-> each 3x3 matrix contains 1-9 exactly once

tc: 9^m,  m => no. of empty cell
sc: o(1)
*/
bool isSafe(int row, int col, vector<vector<int>>& board, int value) {
    for (int i = 0; i < board.size(); i++) {
        //row check
        if (board[row][i] == value)
            return false;
        //col check
        if (board[i][col] == value)
            return false;
        // 3*3 matrix check
        if (board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == value)
            return false;
    }
    return true;
}


bool solve(vector<vector<int>>& board) {
    int n = board[0].size();

    for (int row = 0; row < n; row++) { // row loop
        for (int col = 0; col < n; col++) { // col loop
            //cell empty
            if (board[row][col] == 0) {
                for (int val = 1; val <= 9; val++) { // putting val
                    if (isSafe(row, col, board, val)) {
                        board[row][col] = val;
                        //recursive call
                        bool nextSolPossible = solve(board);
                        if (nextSolPossible)
                            return true;
                        else { //backtrack
                            board[row][col] = 0;
                        }
                    }
                }
                return false;
            }
        }
    }
    return true;
}


void solveSudoku(vector<vector<int>>& sudoku) {
    solve(sudoku);
}