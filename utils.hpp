#ifndef utils_hpp
#define utils_hpp

#include <random>

#include "parameter.hpp"
#include "individual.hpp"

int random_select(individual &indiv, const std::vector<individual> &set){
    std::uniform_int_distribution<> range(0, set.size() - 1);
    int index = range(param::mt);
    indiv = set[index];
    return index;
}

int roulette_select(individual &indiv, std::vector<individual> set){

    double sum_fitness = 0.;
    for(int i = 0; i < set.size(); i++) sum_fitness += set[i].fitness;
    for(int i = 0; i < set.size(); i++) set[i].fitness = sum_fitness - set[i].fitness;
    double roulette_fitness = 0.;
    for(int i = 0; i < set.size(); i++) roulette_fitness += set[i].fitness;
    std::uniform_int_distribution<> roulette(0, roulette_fitness);
    roulette_fitness = roulette(param::mt);    
    int index = 0;
    for(int i = 0; i < set.size(); i++){
        roulette_fitness -= set[i].fitness;
        if(roulette_fitness <= 0){
            index = i;
            indiv = set[i];
        }
    }
    return index;
}

#endif