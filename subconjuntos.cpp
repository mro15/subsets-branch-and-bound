#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>

//identify whether an element of the set has been chosen or not
#define SELECTED 1
#define NOTSELECTED 0
//Set
typedef struct r_set{
    int id;
    int weight;
    int selected;
}r_set;

int main(int argc, char *argv[]){
    std::fstream input;
    char *fileName;
    int id=1, n , k;
    std::vector<r_set> sets;
    r_set aux;
    if(argc!=4){
        std::cout << "Uso: ./subconjuntos <n> <k> <arquivo de entrada>" << std::endl;
        return 0;
    }else{
		n = atoi(argv[1]);
		k = atoi(argv[2]);
        fileName = argv[3];
    }
    input.open(fileName, std::ifstream::in);
    if(!input.good()) {
        std::cout << "Nao foi possivel abrir o arquivo" << std::endl;
        return 0;
    }
    //TODO: guloso para achar um resultado bom pra começar o branch and bound
    //TODO: branch and bound (2 bounds)
    while(id<=n){
		input >> aux.weight;
        aux.id = id;
        aux.selected = NOTSELECTED;
        sets.push_back(aux);
        id++;
    }
    //Print vector
    for(std::vector<r_set>::iterator it = sets.begin(); it != sets.end(); ++it){
        std::cout << (*it).id << " " << (*it).weight << std::endl;
    }
    return 0;
}
