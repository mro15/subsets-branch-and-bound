#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <list>
#include <algorithm>

typedef struct solution{
    std::vector<int> subset;
	float value;
}solution;

std::vector<int> v;
float average;
int n_s;

float calculate_average(int k){
    float average=0;
    for(std::vector<int>::iterator it = v.begin(); it != v.end(); ++it){
        average+= *it;
    }
    return average/k;
}

float calculate_bound(solution s[], int k){
	float bound = 0;
    for(std::vector<int>::iterator it = s[k].subset.begin(); it != s[k].subset.end(); ++it){
		bound+= *it;
    }
	s[k].value = bound;
	return bound;
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

void print_complete_solution(solution s[], int k){
    std::cout << "--------------------------------------------" << std::endl;
    for(int i=k; i>=1; --i){
		std::cout << "K: " << i << " ";
		std::cout <<  "[ ";
        for(std::vector<int>::iterator it = s[i].subset.begin(); it != s[i].subset.end(); ++it){
            std::cout << *it << " " ;
        }
		std::cout << " ]";
	}
    std::cout << std::endl << "--------------------------------------------" << std::endl;
	std::cout << std::endl;
}

void clear_solution(solution s[], int k){
	s[k].subset.clear();
}

int cut(float bound){
    if(bound>average){
        return 1;
    }
    return 0;
}

int enumerate(std::vector<int> v, int n, int k, int offset, std::list<int> &subsets, solution s[]){
    float partial_bound;
    if(k==1 || v.empty()){
		clear_solution(s, k);
		//std::cout << "[ ";
  		for(std::vector<int>::iterator it=v.begin(); it!=v.end() ; it++){
        	//std::cout << *it << " ";
			s[k].subset.push_back(*it);
        }
		//std::cout << "] ";

        partial_bound = calculate_bound(s, k);
		std::cout << "BOUND: " << partial_bound << std::endl;
        if(cut(partial_bound)){
            std::cout << "CUT" << std::endl;
            return 0;
        }
        std::cout << "DONT CUT" << std::endl;
		print_complete_solution(s, n_s);
        return 0;
    }
	if(offset==n){
        if(subsets.empty()) return 0;
		clear_solution(s, k);
		//std::cout << "[ ";
  		for(std::list<int>::iterator it=subsets.begin(); it!=subsets.end() ; ++it){
        	//std::cout << *it << " ";
			s[k].subset.push_back(*it);
			std::vector<int>::iterator i = std::find(v.begin(), v.end(), *it);
			size_t index = std::distance(v.begin(), i);
			v.erase(v.begin() + index);
        }
		//std::cout << "] ";
        partial_bound = calculate_bound(s, k);
		std::cout << "BOUND: " << partial_bound << std::endl;
        if(cut(partial_bound)){
            std::cout << "CUT" << std::endl;
            return 0;
        }
        std::cout << "DONT CUT" << std::endl;
		//debug(v);
        //bound aqui
		std::list<int>subsets2;
		enumerate(v, v.size(), k-1, 0, subsets2, s);
		std::cout << std::endl;
		return 0;
	}
    //bound aqui
	subsets.push_back(v.at(offset));
	enumerate(v, n, k, offset+1, subsets, s);
	subsets.remove(v.at(offset));
	enumerate(v, n, k, offset+1, subsets, s);
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
    solution s[k+1];
	n_s = k;
    average = calculate_average(k);
    std::cout << "MEDIA " << average << std::endl;
    //debug(v);
	enumerate(left, n, k, 0, subsets, s);
    return 0;
}
