#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <list>
#include <algorithm>

typedef struct solution{
    std::vector<int> subset;
}solution;

std::vector<int> v;
float average;

float calculate_average(int k){
    float average=0;
    for(std::vector<int>::iterator it = v.begin(); it != v.end(); ++it){
        average+= *it;
    }
    return average/k;
}
int calculate_bound(solution s, int k){

    for(int i=0; i<k; ++i){
        for(std::vector<int>::iterator it = s.subset.begin(); it != s.subset.end(); ++it){
            std::cout << *it << " " ;
        }
    }
}

void debug(std::vector<int> v){
	std::cout << "DEBUG" << std::endl;
    std::cout << "[ " ;
    for(std::vector<int>::iterator it = v.begin(); it != v.end(); ++it){
        std::cout << *it << " " ;
    }
	std::cout << "] ";
	std::cout << std::endl;
	std::cout << "-------------------------------------------------" << std::endl;
}

int enumerate(std::vector<int> v, int n, int k, int offset, std::list<int> &subsets){
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
        //bound aqui
		std::list<int>subsets2;
		enumerate(v, v.size(), k-1, 0, subsets2);
		std::cout << std::endl;
		return 0;
	}
    //bound aqui
	subsets.push_back(v.at(offset));
	enumerate(v, n, k, offset+1, subsets);
	subsets.remove(v.at(offset));
	enumerate(v, n, k, offset+1, subsets);
	return 0;
}

int main(int argc, char *argv[]){
    std::fstream input;
    char *fileName;
    int id=1, n , k, aux;
	std::list<int> subsets;
	std::vector<int> left;
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
		input >> aux;
		left.push_back(aux);
        v.push_back(aux);
        id++;
    }
    solution s[k];
    average = calculate_average(k);
    std::cout << "MEDIA " << average << std::endl;
    //debug(v);
	enumerate(left, n, k, 0, subsets);
    return 0;
}
