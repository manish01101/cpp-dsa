#include <bits/stdc++.h>
using namespace std;

#define N 4

struct PuzzleState {
    vector<vector<int>> board;
    int g, h;
    string path;

    PuzzleState(vector<vector<int>> b, int g, string path) : board(b), g(g), path(path) {
        h = manhattan();
    }

    int manhattan() const {
        int dist = 0;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j) {
                int val = board[i][j];
                if (val != 0) {
                    int targetX = (val - 1) / N;
                    int targetY = (val - 1) % N;
                    dist += abs(i - targetX) + abs(j - targetY);
                }
            }
        return dist;
    }

    bool operator>(const PuzzleState& other) const {
        return g + h > other.g + other.h;
    }

    bool is_goal() const {
        int count = 1;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                if (i == N - 1 && j == N - 1)
                    return board[i][j] == 0;
                else if (board[i][j] != count++) return false;
        return true;
    }

    string serialize() const {
        string s;
        for (auto& row : board)
            for (int val : row)
                s += to_string(val) + ",";
        return s;
    }
};

vector<pair<int, int>> directions = {
    {-1, 0}, {1, 0}, {0, -1}, {0, 1}
};

vector<char> moveChars = { 'U', 'D', 'L', 'R' };

void print_board(const vector<vector<int>>& board) {
    for (auto& row : board) {
        for (int val : row)
            cout << (val ? to_string(val) : " ") << "\t";
        cout << "\n";
    }
    cout << "----------------------\n";
}

void solve_puzzle(vector<vector<int>> initial) {
    priority_queue<PuzzleState, vector<PuzzleState>, greater<>> pq;
    unordered_set<string> visited;

    PuzzleState start(initial, 0, "");
    pq.push(start);
    visited.insert(start.serialize());

    while (!pq.empty()) {
        auto current = pq.top(); pq.pop();

        if (current.is_goal()) {
            cout << "Solved in " << current.g << " moves.\n";
            cout << "Move sequence: " << current.path << "\n";
            vector<vector<int>> replay = initial;
            print_board(replay);
            for (char move : current.path) {
                int x, y;
                for (int i = 0; i < N; ++i)
                    for (int j = 0; j < N; ++j)
                        if (replay[i][j] == 0) { x = i; y = j; }

                int dx = 0, dy = 0;
                if (move == 'U') dx = -1;
                else if (move == 'D') dx = 1;
                else if (move == 'L') dy = -1;
                else if (move == 'R') dy = 1;

                swap(replay[x][y], replay[x + dx][y + dy]);
                print_board(replay);
            }
            return;
        }

        int zx, zy;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                if (current.board[i][j] == 0) { zx = i; zy = j; }

        for (int d = 0; d < 4; ++d) {
            int nx = zx + directions[d].first;
            int ny = zy + directions[d].second;
            if (nx >= 0 && ny >= 0 && nx < N && ny < N) {
                auto newBoard = current.board;
                swap(newBoard[zx][zy], newBoard[nx][ny]);
                PuzzleState neighbor(newBoard, current.g + 1, current.path + moveChars[d]);
                string key = neighbor.serialize();
                if (visited.find(key) == visited.end()) {
                    visited.insert(key);
                    pq.push(neighbor);
                }
            }
        }
    }

    cout << "No solution found.\n";
}

int main() {
    vector<vector<int>> initial = {
        {1, 2, 3, 4},
        {5, 6, 0, 8},
        {9, 10, 7, 11},
        {13, 14, 15, 12}
    };

    solve_puzzle(initial);
    return 0;
}
