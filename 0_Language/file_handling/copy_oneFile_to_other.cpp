#include<iostream>
#include<fstream>
using namespace std;

int main() {
    ifstream infile("a.txt");
    if(!infile) {
        cerr << "file not opened" << endl;
    }
    ofstream outfile("b.txt");
    if(!outfile) {
        cout  << "file not opened" << endl;
    }
    string str;
    while(getline(infile, str)) {
        outfile << str << endl;
    }
    outfile.close();
    infile.close();
    return 0;
}