#include<iostream>
#include<fstream>
#include<typeinfo>
#include<string>
using namespace std;

/*
1 Open the file using an ifstream object.
2 Read data from the file using input stream operations (>>, getline(), etc.).
3 Close the file.
*/
int main() {
    ifstream infile("a.txt");
    // other way
    // ifstream infile;
    // infile.open("a.txt");

    if (!infile.is_open()) {
        cerr << "file can't opened" << endl;
    }
    string str;
    infile >> str;

    // getline(infile, str);  //this will read a line
    while (getline(infile, str)) {
        cout << str << endl;
    }

    // end of file
    if (infile.eof()) cout << "end of file reached" << endl;
    infile.close();
}