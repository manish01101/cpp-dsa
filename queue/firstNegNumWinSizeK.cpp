#include<iostream>
#include<deque>
#include<vector>
using namespace std;
typedef long long int lli;
typedef long long ll;

vector<ll> firstNegInt(lli A[], lli N, lli K) {
    deque<lli> dq;
    vector<ll> ans;

    //process first window of k-size
    for(int i=0; i<K; i++){
        if(A[i]<0){
            dq.push_back(i);
        }
    }

    //store number of first k sized window
    if(dq.size() > 0){
        ans.push_back(A[dq.front()]);
    }
    else
        ans.push_back(0);

    //process for remaining windows
    for(int i=K; i<N; i++){
        //removal
        if(!dq.empty() && i-dq.front() >= K){ 
            dq.pop_front();
        }

        //addition
        if (A[i]<0){
            dq.push_back(i);
        }

        //ans store
        if(dq.size() > 0){
            ans.push_back(A[dq.front()]);
        }
        else
            ans.push_back(0);
    }
    return ans;
}
int main() {
    lli A[5] = {-8, 2, 3, -6, 10};
    lli N = 5;
    lli K = 2;

    vector<ll> a = firstNegInt(A, N, K);
    for(auto i : a){
        cout << i << " ";
    }
}