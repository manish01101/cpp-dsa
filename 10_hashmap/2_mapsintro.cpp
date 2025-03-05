#include<iostream>
#include<map>
#include<unordered_map>
using namespace std;
/*
map use bst tc: log n
unordered_map use hashing tc: constant
*/
int main() {
    
    //creation
    unordered_map<string, int> m;

    //insertion
    // way 1
    pair<string, int> p = make_pair("manish", 3);
    m.insert(p);

    // way 2
    pair<string, int> p2("kumar", 2);
    m.insert(p2);

    // way 3 : for same key
    m["man"] = 1; //first time - creation
    m["man"] = 2; //next time - updation

    //search
    cout << m["man"] << endl;
    cout << m.at("manish") << endl;

    // cout << m.at("unknownkey") << endl; //error
    cout << m["unknownkey"] << endl; //it will make entry

    // now it throw - 0 as output as it makes entry in above line
    cout << m.at("unknownkey") << endl;

    //size
    cout <<"size"<< m.size() << endl;

    // to check presence
    // count fn-if key present -> 1
    // if key absent -> 0
    cout << m.count("bro") << endl;
    cout << m.count("manish") << endl;

    // erase
    m.erase("manish");
    cout <<"size"<< m.size() << endl;

    //accessing all ele
    for(auto i:m) {
        cout << i.first << " " <<i.second << "\n";
    }

    // iterator
    unordered_map<string, int> :: iterator it = m.begin();

    while(it != m.end()) {
        cout << it->first << " " <<it->second << "\n";
        it++;
    }
}