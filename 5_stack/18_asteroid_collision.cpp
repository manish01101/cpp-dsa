class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        stack<int> s;
        for(int curr: asteroids) {
            bool destroyed = false;
            
            while(!s.empty() and curr < 0 and s.top() > 0) {
                if(abs(s.top()) < abs(curr)) {
                    s.pop();
                    continue;
                }
                else if(abs(s.top()) == abs(curr)) {
                    s.pop();
                }
                destroyed = true;
                break;
            }
            if(!destroyed) {
                s.push(curr);
            }
        }

        vector<int> ans(s.size());
        for (int i = s.size() - 1; i >= 0; i--) {
            ans[i] = s.top();
            s.pop();
        }
        return ans;
    }
};