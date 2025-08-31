// leetcode medium
/*In this problem, we are presented with a grid representing a series of rooms, each of which could be an empty room, a gate, or a blocked wall. The value -1 identifies a wall or obstacle, which means the room cannot be passed through. A value of 0 indicates a gate, serving as a possible destination for other rooms. Any room with a value of INF, which stands for infinity and is given the numerical value of 2147483647, represents an empty room needing the distance filled to its nearest gate.

The task is to update the grid so that all empty rooms have their values changed from INF to the shortest distance to a gate. If there's no way to get to a gate, the value of INF should remain unchanged. The update should be done in place, meaning no additional grid should be constructed but instead, the rooms grid itself should be modified.

*/
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
	void wallsAndGates(vector<vector<int>>& rooms) {
		if (rooms.empty()) return;
		int rows = rooms.size(), cols = rooms[0].size();
		queue<pair<int, int>> q;

		for (int r = 0; r < rows; ++r)
			for (int c = 0; c < cols; ++c)
				if (rooms[r][c] == 0)
					q.emplace(r, c);

		int directions[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };

		while (!q.empty()) {
			auto [r, c] = q.front(); q.pop();
			for (auto& d : directions) {
				int nr = r + d[0], nc = c + d[1];
				if (nr < 0 || nr >= rows || nc < 0 || nc >= cols || rooms[nr][nc] != INT_MAX)
					continue;
				rooms[nr][nc] = rooms[r][c] + 1;
				q.emplace(nr, nc);
			}
		}
	}
	void wallsAndGates2(vector<vector<int>>& rooms) {
		if (rooms.empty()) return;
		int rows = rooms.size(), cols = rooms[0].size();
		queue<pair<int, int>> q;
		for (int row = 0; row < rows; ++row) {
			for (int col = 0; col < cols; ++col) {
				if (rooms[row][col] == 0)
					q.emplace(row, col);
			}
		}
		int directions[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };
		int distance = 0;
		while (!q.empty()) {
			++distance;
			int levelSize = q.size();
			for (int i = 0; i < levelSize; ++i) {
				auto [row, col] = q.front();
				q.pop();
				for (auto& [r, c] : directions) {
					int newRow = row + r;
					int newCol = col + c;
					if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && rooms[newRow][newCol] == INT_MAX) {
						rooms[newRow][newCol] = distance;
						q.emplace(newRow, newCol);
					}
				}
			}
		}
	}
};

int main() {
	const int INF = INT_MAX;

	vector<vector<int>> rooms = {
		{INF,  -1,   0, INF},
		{INF, INF, INF,  -1},
		{INF,  -1, INF,  -1},
		{0,    -1, INF, INF}
	};

	cout << "Original grid:" << endl;
	for (const auto& row : rooms) {
		for (auto cell : row) {
			if (cell == INF) cout << "INF ";
			else cout << cell << " ";
		}
		cout << endl;
	}
	cout << endl;

	Solution().wallsAndGates2(rooms);

	cout << "After running wallsAndGates:" << endl;
	for (const auto& row : rooms) {
		for (auto cell : row) {
			if (cell == INF) cout << "INF ";
			else cout << cell << " ";
		}
		cout << endl;
	}

	return 0;
}
