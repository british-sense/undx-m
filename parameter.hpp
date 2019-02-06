#ifndef parameter_hpp
#define parameter_hpp

#include<random>

namespace param{
    static int n = 20;
    static int trial = 10;
    static int generation = 300;
    static int population = 200;
    static int children = 100;
    static int m = 2;
    static double alpha = 1.;
    static double beta = 0.35;
    static double sigma_xi = alpha / std::sqrt(m);
    static double sigma_eta = (1 / std::sqrt(n - m)) * (std::sqrt(m + 1) / std::sqrt(m + 2)) * (std::sqrt(3) / std::sqrt(2)) * beta;
    static double upper_limit = 5.12;
    static double lower_limit = -5.12;
    std::mt19937 mt(0);
    std::uniform_int_distribution<> range(lower_limit, upper_limit);
}

#endif