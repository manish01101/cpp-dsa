/*
solve a pathfinding problem (likely using Breadth-First Search or BFS) to find the shortest path for a "Hero" ('H') to collect all 'K' keys and reach a 'C' chest in a grid, avoiding 'O' obstacles.
The provided solve function is currently incomplete and has a logical error in its bounds checking condition. You need to implement a search algorithm that considers the state of collected keys.
Here is a corrected and expanded implementation using Breadth-First Search (BFS), which is suitable for finding the shortest path in an unweighted grid.
*/



#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

// Directions: right, down, left, up
vector<int> dirx = {0, 1, 0, -1};
vector<int> diry = {1, 0, -1, 0};

// State tuple for BFS: (row, col, keys_collected_mask, steps)
typedef tuple<int, int, int, int> State;

void solve(vector<vector<char>> &grid, int hi, int hj, int ci, int cj, int totalKeys) {
    int n = grid.size();
    int m = grid[0].size();
    
    // Use a bitmask to represent which keys have been collected.
    // Max totalKeys is often small in competitive programming (e.g., <= 10)
    // visited[row][col][key_mask] = true if visited
    vector<vector<vector<bool>>> visited(n, vector<vector<bool>>(m, vector<bool>(1 << totalKeys, false)));

    queue<State> q;

    // Start state: (hero_row, hero_col, initial_keys_mask, initial_steps)
    // The initial key mask is 0 (no keys collected yet)
    q.push(make_tuple(hi, hj, 0, 0));
    visited[hi][hj][0] = true;

    // A map to store the index of each key 'K' found
    map<pair<int, int>, int> keyMap;
    int keyIdx = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == 'K') {
                keyMap[{i, j}] = keyIdx++;
            }
        }
    }

    while (!q.empty()) {
        State current = q.front();
        q.pop();
        int r = get<0>(current);
        int c = get<1>(current);
        int currentKeysMask = get<2>(current);
        int steps = get<3>(current);

        // Check if we reached the Chest 'C' with all keys
        if (r == ci && c == cj && currentKeysMask == (1 << totalKeys) - 1) {
            cout << steps << endl;
            return;
        }

        // Explore neighbors
        for (int i = 0; i < 4; ++i) {
            int nr = r + dirx[i];
            int nc = c + diry[i];

            // Check bounds
            if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                char nextCell = grid[nr][nc];

                // Check for obstacles
                if (nextCell == 'O') continue;

                int nextKeysMask = currentKeysMask;

                // Collect key if we step on 'K'
                if (nextCell == 'K') {
                    int k_idx = keyMap[{nr, nc}];
                    nextKeysMask |= (1 << k_idx); // Set the corresponding bit
                }

                // Check if this state has been visited
                if (!visited[nr][nc][nextKeysMask]) {
                    visited[nr][nc][nextKeysMask] = true;
                    q.push(make_tuple(nr, nc, nextKeysMask, steps + 1));
                }
            }
        }
    }

    // If the queue is empty and we haven't returned, it's impossible
    cout << "impossible" << endl;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n, m;
    if (!(cin >> n >> m)) return 0; // Handle end of input

    vector<vector<char>> grid(n, vector<char>(m));
    int totalKeys = 0;
    int hi, hj, ci, cj;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] == 'K') totalKeys++;
            if (grid[i][j] == 'H') {
                hi = i;
                hj = j;
            }
            if (grid[i][j] == 'C') {
                ci = i;
                cj = j;
            }
        }
    }

    solve(grid, hi, hj, ci, cj, totalKeys);

    return 0;
}