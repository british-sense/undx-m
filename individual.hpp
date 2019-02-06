#ifndef individual_hpp
#define individual_hpp

#include <vector>

#include "parameter.hpp"

class individual{

    public:
    std::vector<double> gene;
    double fitness;

    public:
    individual() : gene(std::vector<double>(param::n)), fitness(0.){
        init();
        evaluate();
    }
    void init(){
        for(int i = 0; i < param::n; i++) gene[i] = param::range(param::mt);
        fitness = 0.;
    }
    void evaluate(){
        // rastrigin
        double A = 10;
        fitness = A * param::n;
        for(int i = 0; i < param::n; i++) fitness += (gene[i] * gene[i] - A * std::cos(2 * M_PI * gene[i]));
    }
    void select(const std::vector<individual> &population){
        std::uniform_int_distribution<> p_select(0, param::population - 1);
        *this = population[p_select(param::mt)];
    }
};

#endif