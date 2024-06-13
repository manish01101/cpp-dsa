#include<iostream>
#include<fstream>
#include<typeinfo>
#include<string>
using namespace std;
/*
1 Open the file using an ofstream object.
2 Write data to the file using output stream operations (<<).
3 Close the file.
*/
int main() {

    // MODE AVAILABLE => ios::app(i.e. append) & ios::trunc(i.e. truncate, & this is default mode)
    ofstream outfile("a.txt", ios::app); 

    if(!outfile) {
        cerr << "error opening file" << endl;
    }
    outfile << "hello manish" << endl; // if we use endl here means after writing curson move to next line, and without endl append text in same line
    outfile.close();

    // cout << typeid(write).name() << endl;

}