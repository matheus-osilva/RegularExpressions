#include "Digraph.h"
#include "NFA.h"
#include <string>
#include <stack>
#include <queue>

//Função para converter o operador '+' para '*'
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
    
    std::string entry ; //expressão regular
    int numoftests = 4;
    std::cout << "Insira o numero de testes de reconhecimento:" << std::endl;
    std::cin >> numoftests;
    std::cout << "Insira a expressao regular:" << std::endl;
    std::cin >> entry;
    entry = extendplus(entry); //expande de (ab)+ para (ab)(ab)*, por exemplo

    NFA sedgewick (entry);

    //Testa se os textos inseridos são reconhecidos pela expressão regular
    std::cout << "Insira " << numoftests << " textos para o teste:" << std::endl;
    std::vector<std::string> texts;
    std::string text;
    for (int i = 0; i < numoftests; i++)
    {
        std::cout << i + 1 << ": ";
        std::cin >> text;
        texts.push_back(text);
    }
    for (int i = 0; i < texts.size(); i++)
    {
        if (sedgewick.recognizes(texts[i]))
        {
            std::cout << "Reconhece " << texts[i] << std::endl;
        }
        else
        {
            std::cout << "Nao reconhece " << texts[i] << std::endl;
        }
    }
}