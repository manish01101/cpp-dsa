class Solution {
private:
	int solveRec(int i, int j, vector<vector<char>>& matrix, int& sideLen) {
		if (i >= matrix.size() || j >= matrix[0].size())
			return 0;

		int right = solveRec(i, j + 1, matrix, sideLen);
		int diagonal = solveRec(i + 1, j + 1, matrix, sideLen);
		int down = solveRec(i + 1, j, matrix, sideLen);

		if (matrix[i][j] == '1') {
			int currSideLen = 1 + min({ right, diagonal, down });
			sideLen = max(sideLen, currSideLen);
			return currSideLen;
		}
		else {
			return 0;
		}
	}
	int solveMem(int i, int j, vector<vector<char>>& matrix, int& sideLen, vector<vector<int>>& dp) {
		if (i >= matrix.size() or j >= matrix[0].size())
			return 0;

		if (dp[i][j] != -1)
			return dp[i][j];

		int right = solveMem(i, j + 1, matrix, sideLen, dp);
		int diagonal = solveMem(i + 1, j + 1, matrix, sideLen, dp);
		int down = solveMem(i + 1, j, matrix, sideLen, dp);

		if (matrix[i][j] == '1') {
			int currSideLen = 1 + min({ right, diagonal, down });
			sideLen = max(sideLen, currSideLen);
			return dp[i][j] = currSideLen;
		}
		else {
			return dp[i][j] = 0;
		}
	}
	int solveTab(vector<vector<char>>& matrix, int& sideLen) {
		int row = matrix.size();
		int col = matrix[0].size();
		vector<vector<int>> dp(row + 1, vector<int>(col + 1, 0));

		dp[row][col] = 0;

		for (int i = row - 1; i >= 0; --i) {
			for (int j = col - 1; j >= 0; --j) {
				int right = dp[i][j + 1];
				int diagonal = dp[i + 1][j + 1];
				int down = dp[i + 1][j];

				if (matrix[i][j] == '1') {
					int currSideLen = 1 + min({ right, diagonal, down });
					sideLen = max(sideLen, currSideLen);
					dp[i][j] = currSideLen;
				}
				else {
					dp[i][j] = 0;
				}
			}
		}
		return dp[0][0];
	}
	int solveSpcOpt(vector<vector<char>>& matrix, int& sideLen) {
		int row = matrix.size();
		int col = matrix[0].size();

		vector<int> curr(col + 1, 0);
		vector<int> next(col + 1, 0);

		for (int i = row - 1; i >= 0; --i) {
			for (int j = col - 1; j >= 0; --j) {
				int right = curr[j + 1];
				int diagonal = next[j + 1];
				int down = next[j];

				if (matrix[i][j] == '1') {
					int currSideLen = 1 + min({ right, diagonal, down });
					sideLen = max(sideLen, currSideLen);
					curr[j] = currSideLen;
				}
				else {
					curr[j] = 0;
				}
			}
			next = curr;
		}
		return next[0]; // or curr[0];
	}
	/* NOT PASS EVERY TEST CASE */
	// int solveSpcOpt2(vector<vector<char>>& matrix, int& sideLen) { 
	// 	int row = matrix.size();
	// 	int col = matrix[0].size();

	// 	int currCurr = 0;
	// 	int currNext = 0;
	// 	int nextCurr = 0;
	// 	int nextNext = 0;

	// 	for (int i = row - 1; i >= 0; --i) {
	// 		for (int j = col - 1; j >= 0; --j) {
	// 			int right = currNext;
	// 			int diagonal = nextNext;
	// 			int down = nextCurr;

	// 			if (matrix[i][j] == '1') {
	// 				int currSideLen = 1 + min({ right, diagonal, down });
	// 				sideLen = max(sideLen, currSideLen);
	// 				currCurr = currSideLen;
	// 			}
	// 			else {
	// 				currCurr = 0;
	// 			}
	// 		}
	// 		nextCurr = currCurr;
	// 		nextNext = currNext;
	// 	}
	// 	return nextCurr;
	// }

public:
	int maximalSquare(vector<vector<char>>& matrix) {
		int sideLen = 0;
		// using recursion
		// solveRec(0, 0, matrix, sideLen);

		// using rec + memoization -> top-down dp
		// vector<vector<int>> dp(matrix.size()+1, vector<int>(matrix[0].size()+1, -1));
		// solveMem(0, 0, matrix, sideLen, dp);

		// using tabulation -> bottom-up dp
		// solveTab(matrix, sideLen);

		// space optimization (s.c. = O(col))
		// solveSpcOpt(matrix, sideLen);

		// space optimizatioon (s.c = constant);
		solveSpcOpt2(matrix, sideLen);

		return sideLen * sideLen;
	}
};