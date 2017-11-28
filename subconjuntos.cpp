#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <list>
#include <algorithm>

//identify whether an element of the set has been chosen or not
#define SELECTED 1
#define NOTSELECTED 0
//Set
typedef struct r_set{
    int id;
    int weight;
    int selected;
}r_set;

void debug(std::vector<int> v){
	std::cout << "[ " ;
    for(std::vector<int>::iterator it = v.begin(); it != v.end(); ++it){
        std::cout << *it << " " ;
    }
	std::cout << "] ";
	std::cout << std::endl;
}

int enumerate(std::vector<int> v, int n, int k, int offset, std::list<int> &subsets, std::vector<std::vector<int> > &nodes){
	if(k==0 || v.empty())
		return 0;
    if(k==1){
		std::cout << "[ ";
  		for(std::vector<int>::iterator it=v.begin(); it!=v.end() ; it++){
        	std::cout << *it << " ";
        }
		std::cout << "] ";

        return 0;
    }
	if(offset==n){
        if(subsets.empty()) return 0;
		std::cout << "[ ";
  		for(std::list<int>::iterator it=subsets.begin(); it!=subsets.end() ; ++it){
        	std::cout << *it << " ";
			std::vector<int>::iterator i = std::find(v.begin(), v.end(), *it);
			size_t index = std::distance(v.begin(), i);
			v.erase(v.begin() + index);
        }
		std::cout << "] ";
		//debug(v);

		std::list<int>subsets2;
		enumerate(v, v.size(), k-1, 0, subsets2, nodes);
		std::cout << std::endl;
		return 0;
	}
	subsets.push_back(v.at(offset));
	enumerate(v, n, k, offset+1, subsets, nodes);
	subsets.remove(v.at(offset));
	enumerate(v, n, k, offset+1, subsets, nodes);
	return 0;
}

int main(int argc, char *argv[]){
    std::fstream input;
    char *fileName;
    int id=1, n , k;
    std::vector<r_set> sets;
	std::list<int> subsets;
	std::vector<int> left;
	std::vector<std::vector<int> > nodes;
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
		left.push_back(aux.weight);
        id++;
    }
    //Print vector
	enumerate(left, n, k, 0, subsets, nodes);
    std::cout << "----------------------------------------" << std::endl;
    return 0;
}
