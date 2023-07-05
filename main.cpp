#include "Digraph.h"
#include <string>
#include <stack>


int main(){
    //(([a-z])*|([0-9])*)*@(([a-z])+\.)+br
    //((A*B|AC)D)
    std::string entry;
    std::string fullEntry;
    std::cout << "Insira a expressao regular:" << std::endl;
    std::cin >> entry;

    // Transform the sets in regular expressions, represented, for example, as [0-9], in the full set 
    // represented by all elements [0123456789];
    // also transform the complementar sets in the full set without the indicated interval
    for (int i = 0; i < entry.size(); i++)
    {
        if (entry[i] == '-')
        {
            for (char j = entry[i - 1] + 1; j != entry[i + 1] + 1; j++)
            {
                fullEntry.push_back(j);
            }
            i += 1;
        }
        else if (entry[i] == '^')
        {
            int startIndex = i + 1;
            int endIndex = i;
            while (entry[endIndex] != ']') endIndex++;
            std::string set = entry.substr(startIndex, endIndex);
            for (char j = 32; j < 127 ; j++) 
            {
                if (set.find(j) == std::string::npos) fullEntry.push_back(j);
            }
            i = endIndex - 1;
        }
        else 
        {
            fullEntry.push_back(entry[i]);
        }
    }
    Digraph g (fullEntry.size() + 1);
    int finishEdge = fullEntry.size();

    /*Create the edges following the rules:
    a) Concatenation: consecutive characters have the edges in order, for example {AB};
    b) Or: create edges to make alternatives in the path, represented by "|";
    c) Closure: allow to repeat arbitraly parts of the pattern includind the empty pattern,
       represented by "*";
    d) Parentheses: override the default rules;
    e) Wildcard: represented by ".", is any single character;*/
    std::cout << fullEntry << std::endl;
    std::stack<int> parentheses; //will recieve the open parentheses, should be empty after the iteration
    for (int i = 0; i < fullEntry.size() - 1; i++)
    {   
        //std::cout << "caractere testado: " << fullEntry[i] << std::endl;
        if (fullEntry[i] == '|') //Or
        {
            //std::cout << "eh or" << std::endl;
            g.addEdge(parentheses.top(), i + 1);
            int close = i;
            while (fullEntry[close] != ')') close++;
            g.addEdge(i, close);
            continue;
        }
        else if (fullEntry[i] == '*') //Closure
        {
            if (fullEntry[i - 1] == ')')
            {
                g.addEdge(i, parentheses.top());
                g.addEdge(parentheses.top(), i);
            }
            else
            {
                g.addEdge(i, i - 1);
                g.addEdge(i - 1, i);
            }
            //std::cout << "eh closure" << std::endl;

        }
        else if (fullEntry[i] == '(') //Open Parenthesis
        {
            //std::cout << "eh parenteses" << std::endl;
            parentheses.push(i);
        }
        else if (fullEntry[i] == ')') //Close Parenthesis
        {
            //std::cout << "eh parenteses" << std::endl;
            parentheses.pop();
        }
        g.addEdge(i, i+1);
        //std::cout << i << "->" << i + 1 << std::endl;
        //std::cout << "criou o arco -----------" << std::endl;
    }  
    g.print();
}