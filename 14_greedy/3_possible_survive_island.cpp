#include<bits/stdc++.h>
using namespace std;

/*
S -> no. of days to survive
N -> max unit of food can buy each day
M -> unit of food each day to survive

find no. of days to buy food
*/

int minimumDays(int S, int N, int M) {
	int sunday = S / 7;
	int buyingDays = S - sunday;
	int totalFood = S * M;

	int ans = 0;
	if (totalFood % N == 0) {
		ans = (totalFood / N);
	}
	else {
		ans = (totalFood / N) + 1;
	}

	if (ans <= buyingDays) {
		return ans;
	}
	else {
		return -1;
	}
}