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

        // // sphere
        // fitness = 0.;
        // for(int i = 0; i < param::n; i++) fitness += (gene[i] * gene[i]);

        // rastrigin
        double A = 10;
        fitness = A * param::n;
        for(int i = 0; i < param::n; i++) fitness += (gene[i] * gene[i] - A * std::cos(2 * M_PI * gene[i]));
        param::opt_fitness = 1e-7;
    }

    public:
    bool operator<(const individual& rhs)const{
        return fitness < rhs.fitness;
    }
    bool operator>(const individual& rhs)const{
        return fitness > rhs.fitness;
    }
};

#endif