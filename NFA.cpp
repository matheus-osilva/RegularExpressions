#include "NFA.h"

//Constroi o NFA a partir da expressão regular
//A operação OR '|' só funciona em pares, portanto é necessário usar parênteses para mais de dois OR consecutivos
NFA::NFA(std::string regexp) : G(regexp.size() + 1) {
    std::stack<int> ops;
    re = std::vector<char>(regexp.begin(), regexp.end());
    M = re.size();

    for (int i = 0; i < M; i++) {
        int lp = i;
        if (re[i] == '[') {
            int j = i;
            while (re[j] != ']') j++;
            G.addEdge(i, j);
            G.addEdge(j, j + 1);
        }
        if (re[i] == '(' || re[i] == '|') {
            ops.push(i);
        } else if (re[i] == ')') {
            int or_op = ops.top();
            ops.pop();
            if (re[or_op] == '|') {
                lp = ops.top();
                ops.pop();
                G.addEdge(lp, or_op + 1);
            } else {
                lp = or_op;
            }
            G.addEdge(or_op, i);
        }

        if (re[i] == '\\') {
            if (i < M - 1) {
                char nextChar = re[i + 1];
                if (nextChar == '*' || nextChar == '(' || nextChar == ')' || nextChar == '|') {
                    G.addEdge(i, i + 2);
                    G.addEdge(i + 2, i + 3);
                    i++;
                } else {
                    G.addEdge(i, i + 1);
                }
            } else {
                G.addEdge(i, i + 1);
            }
        }

        if (i < M - 1 && re[i + 1] == '*') {
            G.addEdge(lp, i + 1);
            G.addEdge(i + 1, lp);
        }

        if (re[i] == '(' || re[i] == '*' || re[i] == ')' || re[i] == '\\') {
            G.addEdge(i, i + 1);
        }
    }
}

//Verifica se o texto é reconhecido pelo NFA
bool NFA::recognizes(std::string txt) {
    std::vector<int> pc;

    DirectedDFS dfs(G, 0); //Procura os estados iniciais possíveis

    for (int v = 0; v < G.getV(); v++) {
        if (dfs.getMarked(v)) {
            pc.push_back(v); //estado atingível do início
        }
    }

    for (int i = 0; i < txt.length(); i++) {
        std::vector<int> match;

        for (int v : pc) {
            if (v < M) {
                if (re[v] == '\\' && v < M - 1) { //Trata o operador escape, que força outros operadores a serem caracteres
                    char nextChar = re[v + 1];
                    if (nextChar == txt[i]) {
                        match.push_back(v + 2);
                    }
                } 
                else if (re[v] == txt[i] || (re[v] == '.' && re[v - 1] != '\\')) { //Caso em que a letra é igual ou o vértice é um coringa '.'
                    match.push_back(v + 1);
                }
                else if (re[v] == '[') { //Trata intervalos e complementos, abreviados ou não
                    if (re[v + 1] != '^') {
                        if (re[v + 2] == '-') {
                            if (txt[i] >= re[v + 1] && txt[i] <= re[v + 3]) {
                                match.push_back(v + 4);
                            }
                        }
                        else {
                            int closebracket = v;
                            while (re[closebracket] != ']') closebracket++;
                            for (int j = v; j < closebracket; j++) {
                                if (txt[i] == re[j]) {
                                    match.push_back(closebracket + 1);
                                    break;
                                }
                            }
                        }
                    }
                    else {
                        int begin = 48;
                        int end = 123;
                        if (re[v + 3] == '-') {
                            if (txt[i] >= 48 && txt[i] < re[v + 2] || txt[i] < 123 && txt[i] > re[v + 4]) {
                                match.push_back(v + 5);
                            }
                        }
                        else {
                            int closebracket = v;
                            bool equal = false;
                            while (re[closebracket] != ']') closebracket++;
                            for (int j = v; j < closebracket; j++) {
                                if (txt[i] == re[j]) {
                                    equal = true;
                                    break;
                                }
                            }
                            if (!equal) match.push_back(closebracket + 1);
                        }
                    }
                }
            }
        }

        pc.clear();
        dfs = DirectedDFS(G, match);

        for (int v = 0; v < G.getV(); v++) {
            if (dfs.getMarked(v)) pc.push_back(v);
        }
    }

    for (int v : pc) {
        if (v == M) return true;
    }
    return false;
}


NFA::print() {
    G.print();
}