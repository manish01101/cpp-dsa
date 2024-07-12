#include<iostream>
#include<stack>
using namespace std;

bool findRetundant(string& s) {
    stack<char> stk;
    for (int i = 0; i < s.length(); i++) {
        char ch = s[i];

        //if opening bracket or operator
        if (ch == '(' || ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            stk.push(ch);
        }
        //closing bracket or lowercase letter
        else {
            if (ch == ')') {
                bool isRetundant = true;
                while (stk.top() != '(') {
                    char top = stk.top();
                    if (top == '+' || top == '-' || top == '*' || top == '/') {
                        isRetundant = false;
                    }
                    stk.pop(); //removing operator
                }
                stk.pop(); // removing that opening bracket
                if (isRetundant == true) {
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {
    string s = "(a+b)";
    cout << findRetundant(s) << endl;
}