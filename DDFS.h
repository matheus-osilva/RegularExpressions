#ifndef REGEX_DDFS_H
#define REGEX_DDFS_H

#include "Digraph.h"
#include <vector>

class DirectedDFS {
private:
    std::vector<bool> marked;

public:
    DirectedDFS(Digraph& G, int s);

    DirectedDFS(Digraph& G, std::vector<int>& sources);

    bool getMarked(int v);

private:
    void dfs(Digraph& G, int v);
};

#endif //REGEX_DDFS_H