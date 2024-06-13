#include<iostream>
#include<vector>
using namespace std;

void solve() {
  int n, k;
  cin >> n >> k; 
  int arr[n];
  for(int i=0; i<n; i++) {
      arr[i] = n-i;
  }
  if(k==0) {
    for(int i=n; i>=1; i--){
      cout << i << " ";
    }cout << endl;
  }
  else if(k == n-1) {
    for(int i=1; i<=n; i++){
      cout << i << " ";
    }cout << endl;
  }
  else if(k>0 && k < n) {
    for(int i=0; i<n && k>0; i+=2) {
      swap(arr[i], arr[i+1]);
      k--;
    }
    for(int i=0; i<n; i++) {
      cout << arr[i] << " ";
    }cout << endl;
  }
}

int main() {
  int t;
  cin >> t;
  while(t--) solve();
  return 0;
}