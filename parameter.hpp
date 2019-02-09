#ifndef parameter_hpp
#define parameter_hpp

#include <random>

namespace param{
    static int n = 20;
    static int trial = 10;
    static int generation = 10000;
    static int population = 300;
    static int children = 200;
    static int m = 5;
    static double alpha = 1.;
    static double beta = 0.35;
    static double sigma_xi = alpha / std::sqrt(m);
    static double sigma_eta = (1. / std::sqrt(n - m)) * (std::sqrt(m + 1.) / std::sqrt(m + 2.)) * (std::sqrt(3.) / std::sqrt(2.)) * beta;
    static double upper_limit = 5.12;
    static double lower_limit = -5.12;
    static double opt_fitness = 0.;
    std::mt19937 mt;
    std::uniform_real_distribution<> range(lower_limit, upper_limit);
}

#endif

// JGG : 2->0, 3->4, 4->4, 5->9, 6->9, 7->9, 8->10, 9->10 10->10, 15->10, 20->10