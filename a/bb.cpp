#include<iostream>
#include<map>
#include<vector>

using namespace std;

vector<int> topK(vector<int>& nums, int k) {
  map<int,int> mp;
  for(int i=0; i<nums.size(); i++) {
      mp[nums[i]]++;
  }
  
  for(auto i: mp) {
      cout << i.first << "" << i.second << endl;
  }
}

int main() {
  vector<int> nums = {1,1,2,2,3,3,3,4};
  int k = 2;

  vector<int> ans = topK(nums, k);
  for(auto i: ans) {
    cout << i << " " ;
  } cout << '\n';

}