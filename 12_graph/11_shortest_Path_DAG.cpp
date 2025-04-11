#include<iostream>
#include<unordered_map>
#include<list>
#include<stack>
#include<vector>
#include<limits.h>
using namespace std;


class Graph {
public:
    unordered_map<int, list<pair<int, int>>> adjList;
    void addEdge(int u, int v, int weight) {
        adjList[u].push_back({v, weight});
    }
    void printAdjList() {
        for (auto i : adjList) {
            cout << i.first << " ";
            for (auto j : i.second) {
                cout << "(" << j.first << "," << j.second << "), ";
            }
            cout << endl;
        }
    }
    void DFS(int node, unordered_map<int, bool>& isVisited, stack<int>& s) {
        isVisited[node] = true;
        for (auto neighbour : adjList[node]) {
            if (!isVisited[neighbour.first]) {
                DFS(neighbour.first, isVisited, s);
            }
        }
        s.push(node);
    }
    void getShortestPath(int src, vector<int>& dist, stack<int>& s) {
        dist[src] = 0;
        while (!s.empty()) {
            int top = s.top();
            s.pop();

            if (dist[top] != INT_MAX) {
                for (auto neighbour : adjList[top]) {
                    if (dist[top] + neighbour.second < dist[neighbour.first]) {
                        dist[neighbour.first] = dist[top] + neighbour.second;
                    }
                }
            }
        }
    }
};


int main() {
    Graph g;
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 3, 6);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 4, 4);
    g.addEdge(2, 5, 2);
    g.addEdge(3, 4, -1);
    g.addEdge(4, 5, -2);

    g.printAdjList();

    // topological sort
    unordered_map<int, bool> isVisited;
    stack<int> s;
    int totalNode = 6;
    for (int i = 0; i < totalNode; i++) {
        if (!isVisited[i]) {
            g.DFS(i, isVisited, s);
        }
    }
    int src = 0;
    vector<int> dist(totalNode, INT_MAX);

    g.getShortestPath(src, dist, s);
    // ans
    cout << "ans : " << endl;
    for (int i = 0; i < dist.size(); i++) {
        cout << dist[i] << " ";
    }cout << endl;

    return 0;
}
