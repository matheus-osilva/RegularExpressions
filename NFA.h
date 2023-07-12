#ifndef REGEX_NFA_H
#define REGEX_NFA_H

#include "DDFS.h"
#include "Digraph.h"
#include <vector>
#include <stack>

class NFA {
private:
    std::vector<char> re; // match transitions
    Digraph G; // epsilon transitions
    int M; // number of states

public:
    NFA(std::string regexp);
    bool recognizes(std::string txt);
    print();
};

#endif // REGEX_NFA_H