#include<iostream>
#include<unordered_map>
#include<list>
#include<set>
#include<algorithm>
#include<vector>
#include<limits.h>
#include<numeric> // for iota(it.start, it.end, initial Val)
using namespace std;
/*
if rank of parent of two node equal
    -> make one node parent of another node
    -> rank of parent node++
if rank of parent of first node < rank of parent of second node
    -> parent[firstNode] = parent of second node

path compression -> if path of any node is larger then just add to top node to that its length gets decreased
*/

// comparator
bool cmp(vector<int>& a, vector<int>& b) {
    return a[2] < b[2];
}
void makeSet(vector<int>& parent, vector<int>& rank, int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}
int findParent(vector<int>& parent, int node) {
    if (parent[node] == node) {
        return node;
    }
    // recursive call
    return parent[node] = findParent(parent, parent[node]); // this will also handle path compression
}

void unionSet(int u, int v, vector<int>& parent, vector<int>& rank) {
    u = findParent(parent, u);
    v = findParent(parent, v);

    if (rank[u] < rank[v]) {
        parent[u] = v;
    }
    else if (rank[v] < rank[u]) {
        parent[v] = u;
    }
    else {
        parent[v] = u;
        rank[u]++;
    }
}

/*
kruskal algo 
-> no need of adj list, instead use linear data str.
-> that data str. store (weight, u, v) 
-> sort them
-> if two node's parent belongs to different component -> merge them
-> if they belongs to same component -> ignore

TC: sort -> m log m
    findParent & unionSet -> 4 * alpha -> nearly constant
=> TC: = O(m log m)
SC: O(n)
*/
// main fn
int minimumSpanningTree(vector<vector<int>>& edges, int n) {

    sort(edges.begin(), edges.end(), cmp); // sort by weight@index-2

    vector<int> parent(n);
    vector<int> rank(n);
    makeSet(parent, rank, n);
    // or
    // vector<int> parent(n);
    // iota(parent.begin(), parent.end(), 0);
    // vector<int> rank(n, 0);

    int minWeight = 0;

    for (int i = 0; i < edges.size(); i++) {
        int u = findParent(parent, edges[i][0]);
        int v = findParent(parent, edges[i][1]);
        int wt = edges[i][2];

        if (u != v) { // parent is different
            minWeight += wt;
            unionSet(u, v, parent, rank);
        }
    }
    return minWeight;
}

