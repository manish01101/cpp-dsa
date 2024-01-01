#include<iostream>
#include<stack>
using namespace std;

bool ValidParen(string s) {
    stack <char> stk;
    for(int i = 0; i < s.length(); i++) {
        char ch = s[i];
        //if open bracket - store in stack
        if(ch == '[' || ch == '{' || ch == '(') {
            stk.push(ch);
        }
        //closing bracket
        else {
            if(!stk.empty()) {
                char topEle = stk.top();
                if(topEle == '[' && ch == ']' || topEle == '{' && ch == '}' || topEle == '(' && ch == ')') {
                    stk.pop();
                }
                else {
                    return false;
                }
            }
            else {
                return false;
            }
        }
    }
    if(s.empty()) {
        return true;
    }
    else {
        return false;
    }
}

int main() {
    string s = "[({})]";
    cout << ValidParen(s) << endl;
    return 0;
}