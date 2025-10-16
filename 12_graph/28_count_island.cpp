#include<bits/stdc++.h>
using namespace std;

class Solution {
	vector<pair<int, int>> directions = { {0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1} };
	int rowSize, colSize;
	void bfs(vector<vector<char>>& grid, vector<vector<bool>>& isVisited, int row, int col) {
		queue<pair<int, int>> q;
		q.push({ row, col });
		isVisited[row][col] = true;

		while (!q.empty()) {
			auto [r, c] = q.front();
			q.pop();
			for (auto& [dr, dc] : directions) {
				int nr = r + dr, nc = c + dc;
				if (nr >= 0 and nr < rowSize and nc >= 0 and nc < colSize and grid[nr][nc] == '1' and !isVisited[nr][nc]) {
					q.push({ nr,nc });
					isVisited[nr][nc] = true;
				}
			}
		}
	}
public:
	int numIslands(vector<vector<char>>& grid) {
		rowSize = grid.size();
		colSize = grid[0].size();
		int count = 0;
		vector<vector<bool>> isVisited(rowSize, vector<bool>(colSize, false));

		for (int i = 0; i < rowSize; ++i) {
			for (int j = 0; j < colSize; ++j) {
				if (grid[i][j] == '1' and !isVisited[i][j]) {
					bfs(grid, isVisited, i, j);
					count++;
				}
			}
		}
		return count;
	}
};
int main() {
	Solution s;
	vector<vector<char>> grid = { {'1', '1', '1', '0', '1'}, {'1', '0', '0', '0', '0'}, {'1', '1', '1', '0', '1'}, {'0', '0', '0', '1', '1'} };
	int ans = s.numIslands(grid);
	cout << ans << endl;

	grid = { {'1', '0', '0', '0', '1'}, {'0', '1', '0', '1', '0'}, {'0', '0', '1', '0', '0'}, {'0', '1', '0', '1', '0'} };
	ans = s.numIslands(grid);
	cout << ans << endl;
}