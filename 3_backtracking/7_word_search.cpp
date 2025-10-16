class Solution {
	bool isPossible(vector<vector<char>>& board, string word, int row, int col, int index) {
		if (index == word.size()) return true;

		if (row < 0 or row >= board.size() or col < 0 or col >= board[0].size())
			return false;
		if (board[row][col] != word[index])
			return false;
		char temp = board[row][col];
		board[row][col] = '#'; // marking visited

		// check for direction
		int dx[4] = { -1, 1, 0, 0 };
		int dy[4] = { 0, 0, -1, 1 };
		for (int dir = 0; dir < 4; dir++) {
			int newRow = row + dx[dir];
			int newCol = col + dy[dir];
			if (isPossible(board, word, newRow, newCol, index + 1)) {
				board[row][col] = temp; // backtrack before returning
				return true;
			}
		}

		// backtrack
		board[row][col] = temp;
		return false;
	}
public:
	bool exist(vector<vector<char>>& board, string word) {
		for (int i = 0; i < board.size(); ++i) {
			for (int j = 0; j < board[0].size(); ++j) {
				if (isPossible(board, word, i, j, 0)) {
					return true;
				}
			}
		}
		return false;
	}
};