#include<iostream>
#include<unordered_map>
#include<list>
#include<set>
#include<queue>
#include<vector>
using namespace std;
/*
node-> store data
edge-> connecting nodes
representation: adj matrix, list
*/
class Graph {
public:
    unordered_map<int, list<int> > adj;

    void addEdgeList(int u, int v, bool isDirected) {
        //isDirected = 0 -> undirected
        //isDirected = 1 -> directed graph

        //create an edge from u to v
        adj[u].push_back(v);
        if (isDirected == 0) {
            adj[v].push_back(u);
        }
    }
    void printAdjList() {
        for (auto i : adj) {
            cout << i.first << "->";
            for (auto j : i.second) {
                cout << j << ", ";
            } cout << endl;
        }
    }
};



int main() {
    int n;
    cout << "enter the no. of nodes: " << endl;
    cin >> n;

    int m;
    cout << "enter the no. of edges: " << endl;
    cin >> m;

    Graph g;
    cout << "enter edges i.e. connected nodes" << endl;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        // creating an undirected graph
        g.addEdgeList(u, v, 0);
    }

    //printing graph
    g.printAdjList();
}