
#include "Digraph.h"

Digraph::Digraph(int V) {
    this->V = V;
    this->E = 0;
    adj.resize(V, std::vector<int>(V));
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++)
        {
            adj[i][j] = 0;
        }
        
    }
}

int Digraph::getV() {
    return V;
}

int Digraph::getE() {
    return E;
}

void Digraph::addEdge(int v, int w) {
    adj[v][w] = 1;
    E++;
}

void Digraph::removeEdge(int v, int w) {
    if (adj[v][w] == 1)
    {
        adj[v][w] = 0;
        E--;
    }
    
}

std::vector<int> Digraph::getadj(int v) {
    return adj[v];
}


void Digraph::print() {
    std::cout << "Vertices e suas conexoes:\n";
    for (int v = 0; v < V; v++) {
        std::cout << v << ": ";
        for (int w : adj[v]) {
            std::cout << w << " ";
        }
        std::cout << "\n";
        std::cout << "\n";
    }
    std::cout << "----------------" << std::endl;
}

std::vector<int> Digraph::bfs(int s){
    std::vector<bool> marked(V, false);
    std::vector<int> edgeTo(V, -1);
    std::queue<int> queue;
    marked[s] = true;
    queue.push(s);
    while (!queue.empty())
    {
        int v = queue.front();
        queue.pop();
        for (int i = 0; i < V; i++)
        {
            if (adj[v][i] == 1)
            {
                if (!marked[i])
                {
                    edgeTo[i] = v;
                    marked[i] = true;
                    queue.push(i);
                }
            }
        }
    }
    return edgeTo;
}

std::vector<int> Digraph::path(int u, int w, std::vector<int> edgeTo){
    std::vector<int> path;
    if (edgeTo[w] != -1)
    {
        for (int x = w; x != u; x = edgeTo[x])
        {
            path.push_back(x);
        }
    }
    return path;
}

int Digraph::pathSize(std::vector<int> path){
    return path.size();
}