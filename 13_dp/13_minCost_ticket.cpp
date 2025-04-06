class Solution {
    int solveRec(int index, vector<int> &days, vector<int> &costs) {
        if(index >= days.size())
            return 0;
        int costDay = costs[0] + solveRec(index+1, days, costs);

        int i = index;
        while(i < days.size() and days[i] < days[index]+7) i++;
        int costWeek = costs[1] + solveRec(i, days, costs);

        i = index;
        while(i < days.size() and days[i] < days[index]+30) i++;
        int costMonth = costs[2] + solveRec(i, days, costs);

        return min({costDay, costWeek, costMonth});
    }
    int solveMem(int index, vector<int> &days, vector<int> &costs, vector<int> &dp) {
        if(index >= days.size())
            return 0;
        if(dp[index] != -1)
            return dp[index];
        int costDay = costs[0] + solveMem(index+1, days, costs, dp);

        int i=index;
        while(i < days.size() and days[i] < days[index]+7) i++;
        int costWeek = costs[1] + solveMem(i, days, costs, dp);

        i=index;
        while(i < days.size() and days[i] < days[index]+30) i++;
        int costMonth = costs[2] + solveMem(i, days, costs, dp);

        return dp[index] = min({costDay, costWeek, costMonth});
    }
    int solveTab(vector<int> &days, vector<int> &costs) {
        int n = days.size();
        vector<int> dp(n+1, INT_MAX);
        dp[n] = 0;

        for(int i=n-1; i >= 0; i--) {
            int costDay = costs[0] + dp[i+1];

            int j=i;
            while(j < n and days[j] < days[i]+7) j++;
            int costWeek = costs[1] + dp[j];

            j=i;
            while(j < n and days[j] < days[i]+30) j++;
            int costMonth = costs[2] + dp[j];

            dp[i] = min({costDay, costWeek, costMonth});
        }
        return dp[0];
    }
    int solveSpcOpt(vector<int> &days, vector<int>& costs) {
        int ans = 0;
        queue<pair<int, int>> week, month; // {day, cost} // constant space(max -> 7 for week, 30 for month)

        for(int day: days) {
            // remove expired day
            while(!week.empty() and week.front().first+7 <= day)
                week.pop();
            while(!month.empty() and month.front().first+30 <= day)
                month.pop();

            // enter curr day with cost
            week.push({day, ans+costs[1]});
            month.push({day, ans+costs[2]});

            // update ans
            ans = min({ans+costs[0], week.front().second, month.front().second});
        }
        return ans;
    }

public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        // recursion
        // return solveRec(0, days, costs);
        
        // recursion + memoization => top-down dp
        // vector<int> dp(days.size()+1, -1);
        // return solveMem(0, days, costs, dp);

        // tabulation => bottom-up dp
        // return solveTab(days, costs);

        // space optimization
        return solveSpcOpt(days, costs);
    }
};