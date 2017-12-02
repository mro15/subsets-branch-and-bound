#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <list>
#include <algorithm>
#include <cmath>

typedef struct solution{
    std::vector<int> subset;
	float value;
}solution;

std::vector<int> v;
float average;
int n_cut = 0, n_s;

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

int cut2(solution s[], int k, std::vector<int> v){ 
	float f1 = calculate_bound(s, k), sum = 0, f2;
	if(k!=1){	
    	for(std::vector<int>::iterator it = v.begin(); it != v.end(); ++it){
      		sum+=*it;
    	}
		f2=sum/k-1;
	}else{
		f2 = 0;
	}
	float f = std::max(f1, f2);
	if(f1 < f2)
		return 1;
	return 0;
	
}

void evaluate_solution(solution s[], solution best[], int k){
	int sum1 = 0, sum2 = 0;
	//if solution is null, the found solution is the best
	if(best[k].subset.empty()){
		for(int i=1; i<=k; ++i){
			best[i].subset.assign(s[i].subset.begin(), s[i].subset.end());
			best[i].value = s[i].value;
		}
	}else{
		//else, get the sum of the candidate solution and best solution.
		// if the candidate solution is better than best, candidate will
		//become the new best.
		for(int i=1; i<=k-1; ++i){
			sum1 += std::abs(s[i].value - s[i+1].value);
			sum2 += std::abs(best[i].value - best[i+1].value);
		}
		if(sum1<sum2){
			for(int i=1; i<=k; ++i){
				best[i].subset.assign(s[i].subset.begin(), s[i].subset.end());
				best[i].value = s[i].value;
			}
		}
	}
	return;
}

int cut(solution s[], int k, std::vector<int> v){
	float f1 = calculate_bound(s, k);
	float sum = 0, f2, f;
	if(v.empty() && k>1)
		return 1;
	if(k==1)
		f = average;
	else{
    	for(std::vector<int>::iterator it = v.begin(); it != v.end(); ++it){
      		sum+=*it;
    	}
		f2=sum/k-1;
		f = std::min(average, f2);
	}
    if(f1<int(f)){
        return 1;
    }
    return 0;
}

int enumerate(std::vector<int> v, int n, int k, int offset, std::list<int> &subsets, solution s[], solution best[]){
    if(k==1 || v.empty()){
		clear_solution(s, k);
  		for(std::vector<int>::iterator it=v.begin(); it!=v.end() ; it++){
			s[k].subset.push_back(*it);
        }
        if(cut(s, k, v)){
			n_cut++;
            return 0;
        }
		evaluate_solution(s, best, n_s);
        return 0;
    }
	if(offset==n){
        if(subsets.empty()) return 0;
		clear_solution(s, k);
  		for(std::list<int>::iterator it=subsets.begin(); it!=subsets.end() ; ++it){
			s[k].subset.push_back(*it);
			std::vector<int>::iterator i = std::find(v.begin(), v.end(), *it);
			size_t index = std::distance(v.begin(), i);
			v.erase(v.begin() + index);
        }
        if(cut(s, k, v)){
			n_cut++;
            return 0;
        }
		std::list<int>subsets2;
		enumerate(v, v.size(), k-1, 0, subsets2, s, best);
		return 0;
	}
	subsets.push_back(v.at(offset));
	enumerate(v, n, k, offset+1, subsets, s, best);
	subsets.remove(v.at(offset));
	enumerate(v, n, k, offset+1, subsets, s, best);
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
    while(id<=n){
		input >> aux;
		left.push_back(aux);
		v.push_back(aux);
        id++;
    }
	n_s = k;
    solution s[k+1];
	solution best[k+1];
    average = calculate_average(k);
	//vector is in the order of entry
	enumerate(left, n, k, 0, subsets, s, best);
	//print best solution
	std::cout << "Melhor solucao na ordem de entrada" << std::endl;
	print_complete_solution(best, n_s);
	std::cout << "Numero de nos cortados: " << n_cut << std::endl;
	//sort vector
	std::sort(v.begin(), v.end());
	//clear old solutions
	for(int i=1; i<=k; ++i){
		clear_solution(s, k);
		clear_solution(best, k);
	}
	//clear number of cut nodes
	n_cut = 0;
	enumerate(v, n, k, 0, subsets, s, best);
	std::cout << "Melhor solucao na ordem crescente" << std::endl;
	print_complete_solution(best, n_s);
	std::cout << "Numero de nos cortados: " << n_cut << std::endl;
    return 0;
}
