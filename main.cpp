#include "Digraph.h"
#include <string>
#include <stack>
#include <queue>

std::string extendplus(std::string entry){
    int plus_ind;
    std::stack<int> parenteshes;
    bool saturou = false;
    int i = 0;
    int size = entry.size();
    while (i < size)
    {
        std::string aux = "";
        if (entry[i] == '(') parenteshes.push(i);
        else if (entry[i] == '+')
        {
            if (entry[i - 1] == ')')
            {
                aux.append(entry.substr(0, i));
                aux.append(entry.substr(parenteshes.top(), i - parenteshes.top()));
                aux.push_back('*');
                aux.append(entry.substr(i + 1));
                entry = aux;
                parenteshes.pop();
                size = entry.size();
            }
            else
            {
                aux.append(entry.substr(0, i));
                aux.push_back(entry[i - 1]);
                aux.push_back('*');
                aux.append(entry.substr(i + 1));
                entry = aux;
                size = entry.size();
            }
        }
        i++;
    }
    return entry;
}



int main(){
    
    //(([a-z])*|([0-9])*)*@(([a-z])+\.)+br
    //((A*B|AC)D)
    // 48 - 123
    std::string entry = "(([a-z])*|([0-9])*)*@(([a-z])+\\.)+br";
    std::string fullEntry = extendplus(entry);
    entry = fullEntry;
    fullEntry = "";
    std::cout << "Insira a expressao regular:" << std::endl;
    //std::cin >> entry;
    std::cout << entry << std::endl;
    
    // Transform the sets in regular expressions, represented, for example, as [0-9], in the full set 
    // represented by all elements [0123456789];
    // also transform the complementar sets in the full set without the indicated interval
    for (int i = 0; i < entry.size(); i++)
    {
        if (entry[i] == '[')
        { 
            if (entry[i + 1] == '^')
            {
                int startIndex = i + 1;
                int endIndex = i;
                while (entry[endIndex] != ']') endIndex++;
                std::string set = entry.substr(startIndex, endIndex);
                for (char j = 48; j < 123 ; j++) 
                {
                    if (set.find(j) == std::string::npos) fullEntry.push_back(j);
                }
                i = endIndex;
            }
            else
            {
                for (char j = entry[i + 1]; j != entry[i + 3] + 1 ; j++)
                {
                    fullEntry.push_back(j);
                }
                i += 4;
            }

        }
        else 
        {
            fullEntry.push_back(entry[i]);
        }
    }
    std::cout << fullEntry << std::endl;
    Digraph g (fullEntry.size() + 1);
    int finishEdge = fullEntry.size();

    /*Create the edges following the rules:
    a) Concatenation: consecutive characters have the edges in order, for example {AB};
    b) Or: create edges to make alternatives in the path, represented by "|";
    c) Closure: allow to repeat arbitraly parts of the pattern includind the empty pattern,
       represented by "*";
    d) Parentheses: override the default rules;
    e) Wildcard: represented by ".", is any single character;
    f) Specified sets: a sequence of characters within square brackets represents any one of those characters;
    g) Range: the sequence within square brackets can represent a range of chars;
    h) Complement: if preceded by "^" the sequence withing square brackets represent any character but one of those characters.
    i) Escape: represented by "\", is used to specify that the char is not a rule, for example "\*" is not a closure;
    j) Plus: same as closure, but does not include the empty pattern, represented by "+".
    */
    std::stack<int> parentheses; //will recieve the open parentheses, should be empty after the iteration
    for (int i = 0; i < fullEntry.size(); i++)
    {   
    
        std::cout << "caractere testado: " << fullEntry[i] << std::endl;
        if (fullEntry[i] == '|') //Or
        {
            std::cout << "eh or" << std::endl;
            g.addEdge(parentheses.top(), i + 1);
            int close = i;
            while (fullEntry[close] != ')') close++;
            g.addEdge(i, close);
            continue;
        }
        else if (fullEntry[i] == '\\'){
            g.addEdge(i + 1, i + 2);
            i = i + 2;
            continue;
        }
        else if (fullEntry[i] == '*') //Closure
        {
            if (fullEntry[i - 1] == ')')
            {
                if (parentheses.empty())
                {
                    g.addEdge(i, 0);
                    g.addEdge(0, i);
                }
                else
                {
                    g.addEdge(i, parentheses.top());
                    g.addEdge(parentheses.top(), i);
                }
            }
            else
            {
                g.addEdge(i, i - 1);
                g.addEdge(i - 1, i);
            }
            std::cout << "eh closure" << std::endl;

        }
        else if (fullEntry[i] == '(') //Open Parenthesis
        {
            std::cout << "eh parenteses" << std::endl;
            parentheses.push(i);
        }
        else if (fullEntry[i] == ')') //Close Parenthesis
        {
            std::cout << "eh parenteses" << std::endl;
            parentheses.pop();
        }
        g.addEdge(i, i+1);
        std::cout << i << "->" << i + 1 << std::endl;
        std::cout << "criou o arco -----------" << std::endl;
    }  
    g.print();
}