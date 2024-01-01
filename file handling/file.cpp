#include<iostream>
#include<fstream>
#include<typeinfo>
#include<string>
using namespace std;

int main() {
    // string s = "this is a input string for the file.";
    // ofstream write("a.txt");
    // write << s;

    // cout << typeid(write).name() << endl;

    //reading file
    string s2;
    ifstream read("a.txt");
    read >> s2;  //this will read only one word
    // getline(read, s2);  //this will read a line
    cout << s2 << endl;

}