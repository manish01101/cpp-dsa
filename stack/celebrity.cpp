#include<iostream>
#include<vector>
#include<stack>
using namespace std;

class Solution{
    private:
    bool knows(vector<vector<int> >&M, int a, int b, int n) {
        if(M[a][b] == 1)
            return true;
        else
            return false;
    }
    public:
    int celebrity(vector<vector<int> >&M, int n) {
        //step1 : push all element in stack
        stack<int> s;
        for(int i=0; i<n; i++) {
            s.push(i);
        }

        //step2 :
        while(s.size() > 1) {
            int a = s.top();
            s.pop();
            
            int b = s.top();
            s.pop();
            
            if(knows(M, a, b, n)) {
                s.push(b);
            }
            else {
                s.push(a);
            }

            //step 3 : single element in stack is potential celeb
            //that single element
            int potCandidate = s.top();

            //so verify it
            bool rowCheck = false;
            int zeroCount = 0;

            for(int i = 0; i < n; i++) {
                if(M[potCandidate][i] == 0) 
                    zeroCount++;
            }
            //all zeroes
            if(zeroCount == n) {
                rowCheck = true;
            }
            //column check
            bool colCheck = false;
            int oneCount = 0;

            for(int i = 0; i<n; i++) {
                if(M[i][potCandidate] == 1)
                    oneCount++;
            }

            if(oneCount == n-1) {
                colCheck = true;
            }
            
            if(rowCheck == true && colCheck == true) {
                return potCandidate;
            }
            else 
                return -1;
        }
    }

};
int main() {
    Solution s;
    vector<vector<int>> m = {{0, 1, 0}, {0, 0, 0}, {0, 1, 0}};
    int n = 3;
    cout << s.celebrity(m, n) << endl;
}