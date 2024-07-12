#include<iostream>
#include<stack>
using namespace std;
/*
no.of open = no. of close
every close brace should have open brace before it

invalid string type:
    1=> {{{{...
    2=> }}}}...
    3=> ...}}}{{{...
*/
int findMinCost(string s) {
    if (s.length() % 2 == 1) {
        return -1;
    }

    stack<char> stk;
    for (int i = 0; i < s.length(); i++) {
        char ch = s[i];
        //opening bracket
        if (ch == '{') {
            stk.push(ch);
        }
        //closing bracket
        else {
            if (!stk.empty() && stk.top() == '{') {
                stk.pop();
            }
            else {
                stk.push(ch);
            }
        }
    }
    //now stack contains only invalid expression
    //a - closing , b - opening
    int a = 0, b = 0;
    while (!stk.empty()) {
        if (stk.top() == '{') {
            b++;
        }
        else {
            a++;
        }
        stk.pop();
    }
    int ans = (a + 1) / 2 + (b + 1) / 2;
    return ans;
}


int main() {
    string s = "}}}}}}";
    cout << findMinCost(s) << endl;
}