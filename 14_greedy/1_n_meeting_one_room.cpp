#include<bits/stdc++.h>
using namespace std;

/*
start and end time given
sort by end time

meeting possible if starting time of next meeting > ending time of curr meeting
*/

int maxMeeting(int start[], int end[], int n) {
	vector<pair<int, int>> v;
	for (int i = 0; i < n; i++) {
		pair<int, int> p = make_pair(start[i], end[i]);
		v.push_back(p);
	}

	sort(v.begin(), v.end(), [](pair<int, int>& a, pair<int, int>& b) {
		return a.second < b.second;
		});

	int count = 1;
	int endingTime = v[0].second;

	for (int i = 1; i < n; i++) {
		if (v[i].first > endingTime) {
			count++;
			endingTime = v[i].second;
		}
	}
	return count;
}

/* -- print meeting number -- */
vector<int> maxMeetings(int N, vector<int>& S, vector<int>& F) {
	// vector<pair<pair<start, end>, position>>
	vector < pair<pair<int, int>, int>> v;
	for (int i = 0; i < N; i++) {
		pair<int, int> p = { S[i], F[i] };
		v.push_back({ p, i + 1 });
	}

	sort(v.begin(), v.end(), [](pair<pair<int, int>, int>& a, pair<pair<int, int>, int>& b) {
		return a.first.second < b.first.second;
		});

	vector<int> ans;
	ans.push_back(v[0].second);
	int endingTime = v[0].first.second;

	for (int i = 1; i < N; i++) {
		if (v[i].first.first > endingTime) {
			ans.push_back(v[i].second);
			endingTime = v[i].first.second;
		}
	}
	sort(ans.begin(), ans.end());
	return ans;
}