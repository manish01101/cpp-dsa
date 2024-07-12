#include<stack>
#include<iostream>
using namespace std;

/*
approach 1: tc:1 sc: n
push
	i. i/p -> normal push
	ii. mini value => 2nd stack
pop
	i. pop from both stack
getMin()
	return 2nd stack top

approach 2:
push:-> check for overflow condition
	->  for 1'st ele -> normal push
			-> update mini
	->  rest ele
		-> if(curr < mini)
			-> val = 2*curr - mini
			-> push(val)
			-> mini update
		-> else normal push
pop: -> check underflow condition
	-> if (curr > mini) : normal pop()
	-> else
		val = 2*mini - curr
		mini = val
		pop()
*/
class SpecialStack {
private:
	stack<int> s;
	int mini;

public:
	void push(int data) {
		if (s.empty()) {
			s.push(data);
			mini = data;
		}
		else {
			if (data < mini) {
				s.push(2 * data - mini);
				mini = data;
			}
			else {
				s.push(data);
			}
		}
	}
	int pop() {
		if (s.empty()) {
			return -1;
		}
		int curr = s.top();
		s.pop();
		if (curr > mini) {
			return curr;
		}
		else {
			int prevMin = mini;
			int val = 2 * mini - curr;
			mini = val;
			return prevMin;
		}
		return -1;
	}
	int top() {
		if (s.empty()) {
			return -1;
		}
		int curr = s.top();
		if (curr < mini) {
			return mini;
		}
		else {
			return curr;
		}
	}
	bool isEmpty() {
		return s.empty();
	}
	int getMin() {
		if (s.empty()) {
			return -1;
		}
		return mini;
	}
};
