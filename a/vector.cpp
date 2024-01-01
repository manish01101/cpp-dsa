#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main(){
    vector<int> v = {5, 2, 6,1,0};
    sort(v.begin(), v.end());
    for(auto a:v){
        cout << a << " ";
    }
    cout << endl;
    sort(v.rbegin(), v.rend());
    for(auto a:v){
        cout << a << " ";
    }
    cout << endl;
}
