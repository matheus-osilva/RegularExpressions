#include "DDFS.h"

DirectedDFS::DirectedDFS(Digraph& G, int s) {
    marked.resize(G.getV());
    for (int i = 0; i < marked.size(); i++)
    {
        marked[i] = false;
    }
    
    dfs(G, s);
}
DirectedDFS::DirectedDFS(Digraph& G, std::vector<int>& sources) {
    marked.resize(G.getV());
    for (int s : sources) {
        if (!marked[s]) dfs(G, s);
    }
}
bool DirectedDFS::getMarked(int v) {
    return marked[v];
}
void DirectedDFS::dfs(Digraph& G, int v) {
    marked[v] = true;
    std::vector<int> adj = G.getadj(v);
    for (int w = 0; w < adj.size(); w++) {
        if (adj[w] == 1)
        {
            if (!marked[w]) dfs(G, w);
        }  
    }
}