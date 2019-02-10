#ifndef utils_hpp
#define utils_hpp

#include <random>
#include <algorithm>

#include "parameter.hpp"
#include "individual.hpp"

individual best_select(const std::vector<individual> &set, std::vector<int> &index_list){

    int index = 0;
    double min = 1e12;
    for(size_t i = 0; i < set.size(); i++){
        if(min > set[i].fitness){
            min = set[i].fitness;
            index = i;
        }
    }
    index_list.push_back(index);
    return set[index];
}

individual random_select(const std::vector<individual> &set, std::vector<int> &index_list){
    std::uniform_int_distribution<> range(0, set.size() - 1);
    int index = range(param::mt);
    while(std::find(index_list.begin(), index_list.end(), index) != index_list.end()){
        index = range(param::mt);
    }
    index_list.push_back(index);
    return set[index];
}

individual roulette_select(const std::vector<individual> &set, std::vector<int> &index_list){

    double sum_fitness = 0.;
    std::vector<individual> roulette_set(set);
    for(size_t i = 0; i < set.size(); i++) sum_fitness += set[i].fitness;
    for(size_t i = 0; i < set.size(); i++) roulette_set[i].fitness = sum_fitness - set[i].fitness;
    sum_fitness = 0.;
    for(size_t i = 0; i < roulette_set.size(); i++) sum_fitness += roulette_set[i].fitness;
    std::uniform_real_distribution<> roulette(0, sum_fitness);
    double roulette_fitness = roulette(param::mt);    
    int index = 0;
    for(size_t i = 0; i < roulette_set.size(); i++){
        roulette_fitness -= roulette_set[i].fitness;
        if(roulette_fitness <= 0){
            index = i;
            break;
        }
    }
    index_list.push_back(index);
    return set[index];
}

#endif