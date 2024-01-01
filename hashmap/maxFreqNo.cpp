
#include<iostream>
#include<map>
#include<unordered_map>
using namespace std;

int maxFreq(vector<int> &arr, int n) {
    unordered_map<int, int> m;

    int maxFreq = 0;
    int maxAns = 0;

    for(int i=0; i<arr.size(); i++) {
        m[arr[i]]++;
        maxFreq = max(maxFreq, m[arr[i]]);
    }
    //for finding first maxfreq ele
    for(int i=0; i<arr.size(); i++) {
        if(maxFreq == m[arr[i]]) {
            maxAns = arr[i];
            break;
        }
    }
    return maxAns;
}