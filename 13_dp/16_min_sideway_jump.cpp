class Solution {
private:
	int solveRec(vector<int>& obstacles, int currLane, int currPos) {
		int n = obstacles.size() - 1;
		if (currPos == n)
			return 0;

		if (obstacles[currPos + 1] != currLane) { // no obstacle->move forward
			return solveRec(obstacles, currLane, currPos + 1);
		}
		else { // obstacles present
			int ans = INT_MAX;
			for (int lane = 1; lane <= 3; lane++) {
				if (currLane != lane and obstacles[currPos] != lane) {
					ans = min(ans, 1 + solveRec(obstacles, lane, currPos));
				}
			}
			return ans;
		}
	}
	int solveMem(vector<int>& obstacles, int currLane, int currPos,
		vector<vector<int>>& dp) {
		int n = obstacles.size() - 1;
		if (currPos == n)
			return 0;
		if (dp[currLane][currPos] != -1)
			return dp[currLane][currPos];

		if (obstacles[currPos + 1] != currLane) {
			return dp[currLane][currPos] = solveMem(obstacles, currLane, currPos + 1, dp);
		}
		else {
			int ans = INT_MAX;
			for (int lane = 1; lane <= 3; lane++) {
				if (currLane != lane and obstacles[currPos] != lane) {
					ans = min(ans, 1 + solveMem(obstacles, lane, currPos, dp));
				}
			}
			return dp[currLane][currPos] = ans;
		}
	}
	/*
		top-down => src = (2, 0) to dest=(1,n) or (2,n) or (3,n)
		so, in bottom-up => src = (1,n) or (2,n) or (3,n) to desc=(2,0)
	 */
	int solveTab(vector<int>& obstacles) {
		int n = obstacles.size() - 1;
		vector<vector<int>> dp(4, vector<int>(obstacles.size(), INT_MAX));
		// base case analyze
		dp[0][n] = 0;
		dp[1][n] = 0;
		dp[2][n] = 0;
		dp[3][n] = 0;

		for (int currPos = n - 1; currPos >= 0; currPos--) {
			for (int currLane = 1; currLane <= 3; currLane++) {
				if (obstacles[currPos + 1] != currLane) {
					dp[currLane][currPos] = dp[currLane][currPos + 1];
				}
				else {
					int ans = INT_MAX;
					for (int lane = 1; lane <= 3; lane++) {
						if (currLane != lane and obstacles[currPos] != lane) {
							ans = min(ans, 1 + dp[lane][currPos + 1]); // not dp[lane][currpos] bcz that is not processed yet
						}
					}
					dp[currLane][currPos] = ans;
				}
			}
		}
		int ansLane1 = dp[1][0];
		int ansLane2 = dp[2][0];
		int ansLane3 = dp[3][0];
		return min({ 1 + ansLane1, ansLane2, 1 + ansLane3 }); // from lane 1 and 3 -> jump to lane 2 for final ans
	}
	int solveSpcOpt(vector<int>& obstacles) {
		int n = obstacles.size() - 1;
		vector<int> curr(4, INT_MAX);
		vector<int> next(4, INT_MAX);

		// base case
		next[0] = 0;
		next[1] = 0;
		next[2] = 0;
		next[3] = 0;

		for (int currPos = n - 1; currPos >= 0; currPos--) {
			for (int currLane = 1; currLane <= 3; currLane++) {
				if (obstacles[currPos + 1] != currLane) {
					curr[currLane] = next[currLane];
				}
				else {
					int ans = INT_MAX;
					for (int lane = 1; lane <= 3; lane++) {
						if (currLane != lane and obstacles[currPos] != lane) {
							ans = min(ans, 1 + next[lane]);
						}
					}
					curr[currLane] = ans;
				}
			}
			next = curr;
		}
		int ansLane1 = next[1];
		int ansLane2 = next[2];
		int ansLane3 = next[3];
		return min({ 1 + ansLane1, ansLane2, 1 + ansLane3 }); // from lane 1 and 3 -> jump to lane 2 for final ans
	}

public:
	int minSideJumps(vector<int>& obstacles) {
		int currLane = 2;
		int currPos = 0;
		// recursion
		// return solveRec(obstacles, currLane, currPos);

		// rec+mem top-down dp
		// vector<vector<int>> dp(4, vector<int>(obstacles.size(), -1));
		// return solveMem(obstacles, currLane, currPos, dp);

		// tabulation -> bottom-up dp
		// return solveTab(obstacles);

		// space optimization
		return solveSpcOpt(obstacles);
	}
};