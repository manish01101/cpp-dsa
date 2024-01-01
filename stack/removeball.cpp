#include<iostream>
#include<stack>
#include<vector>
using namespace std;
class Solution {
  public:
    int finLength(int N, vector<int> color, vector<int> radius) {
        stack<int> colorstk;
        colorstk.push(-1);
        stack<int> radiusstk;
        radiusstk.push(-1);
        for(int i = 0; i < N; i++) {
            int c = color[i];
            int r = radius[i];
            if(!colorstk.empty() && !radiusstk.empty() && colorstk.top() == c && radiusstk.top() == r) {
                colorstk.pop();
                radiusstk.pop();
            }
            else {
                colorstk.push(c);
                radiusstk.push(r);
            }
        }
        //finding length
        int count = 0;
        while(!colorstk.empty() && !colorstk.empty()) {
            count++;
            colorstk.pop();
            radiusstk.pop();
        }
        return count-1;
    }
    
};