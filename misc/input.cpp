#include<iostream>
#include<sstream>
using namespace std;

/*------- integer array input ---------*/
vector<int> input_arr_format() {
    string input;
    getline(cin, input);

    // Replace any non-digit and non-minus characters with spaces
    for (char& c : input) {
        if (!isdigit(c) && c != '-') {
            c = ' ';
        }
    }
    stringstream ss(input);
    vector<int> arr;
    int num;
    while (ss >> num) {
        arr.push_back(num);
    }

    return arr;
}
// vector<int> input_space_separated() {
//     string input;
//     getline(cin, input);
//     stringstream ss(input);
    
//     vector<int> arr;
//     int num;
//     while(ss >> num) {
//         arr.push_back(num);
//     }
//     return arr;
// }




/*------- string array input ---------*/
vector<string> input_string_arr() {
    string input;
    getline(cin, input);

    // if input is only white space separated then don't use the below
    // for(char &c: input) {
    //     if(!isalnum(c)) {
    //         c = ' ';
    //     }
    // }

    // comma separated
    for(char &c: input) {
        if(c == ',') { // replace comma with space
            c = ' ';
        }
    }
    stringstream ss(input);
    vector<string> arr;
    string temp;
    while(ss >> temp) {
        arr.push_back(temp);
    }
    return arr;
}

void freq(vector<int> &arr, unordered_map<int, int> &mp) {
    for(auto &a : arr) {
        mp[a]++;
    }
}
int main() {
    /* ---- if size not given ----------*/
    // vector<int> arr = input_arr_format();
    // vector<int> arr = input_space_separated();
    

    /* ------ take size -----*/
    // int n;
    // cin >> n;

    /* ------- take arr ele -----*/
    // vector<int> arr(n);
    // for(int i=0; i<n; i++) {
    //     cin >> arr[i];
    // }

    /*------or use this format-------*/
    // vector<int> arr;
    // int temp;
    // for(int i=0; i<n; ++i) {
    //     cin >> temp;
    //     arr.push_back(temp);
    // }


    /* ------- perform operation --------*/
    // int sum = 0;
    // for(auto &a : arr) sum+=a;
    // cout << sum;

    // unordered_map<int, int> mp;
    // freq(arr, mp);
    // for(auto &[key, val] : mp) {
    //     cout << key << " " << val << endl;
    // }


    // taking string arr input
    vector<string> str = input_string_arr();
    for (auto& a : str) cout << a << endl;
}