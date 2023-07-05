#ifndef DNAGRAPH_GRAPHS_H
#define DNAGRAPH_GRAPHS_H

#include <vector>
#include <iostream>
#include <queue>



class Digraph {
private:
    int V;
    int E;
    std::vector<std::vector<int>> adj;

public:
    Digraph(int V);
    int getV();
    int getE();
    void addEdge(int v, int w);
    void removeEdge(int v, int w);
    std::vector<int> getadj(int v);
    void print();
    std::vector<int> bfs(int s);
    std::vector<int> path(int u, int w, std::vector<int> edgeTo);
    int pathSize(std::vector<int> path);
};

#endif // DNAGRAPH_GRAPHS_H
