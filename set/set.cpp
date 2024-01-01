#include<iostream>
#include<set>
using namespace std;

int main(){
    int arr[7] = {1, 3, 2, 1, 5, 3,2};
    set<int> st;
    for(int i = 0; i<7; i++){
        st.insert(arr[i]);
    }
    for(auto i : st){
        cout << i << " ";
    }
    cout << endl << *(st.find(7)) << endl;
}