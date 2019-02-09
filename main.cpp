#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

#include "parameter.hpp"
#include "utils.hpp"
#include "individual.hpp"
#include "vector.hpp"

int main(){

    std::cout << "number of trial : " << param::trial
    std::cout << "number of generation : " << param::generation
    std::cout << "population size : " << param::population
    std::cout << "children size : " << param::children
    std::cout << "number of parents : " << param::m
    std::cout << "number of dimention : " << param::n

    int opt_count = 0;

    for(int t = 1; t <= param::trial; t++){

        param::mt = std::mt19937(t);

        // 母集団の生成
        std::vector<individual> population(param::population);

        for(int g = 1; g <= param::generation; g++){

            // m + 1個の親子体x_i(i = 1, ..., m + 1)をランダムに選択する
            std::vector<int> parent_index;
            std::vector<individual> parents;
            for(int i = 0; i < param::m + 1; i++) parents.push_back(random_select(population, parent_index));

            // 親子体の重心pを求める
            std::vector<double> p(param::n, 0);
            for(int i = 0; i < param::m + 1; i++) p += parents[i].gene;
            p /= (param::m + 1);

            // pと各個体x_iの差分ベクトルd_i = x_i - pを求める
            std::vector<std::vector<double> > d;
            for(int i = 0; i < param::m + 1; i++) d.push_back(parents[i].gene - p);

            // m + 2番目の親子体x_(m + 2)をランダムに選択する
            parents.push_back(random_select(population, parent_index));

            // d_1, ..., d_mが張る面の法線nを求める
            std::vector<double> n(param::n);
            n = normal(d);

            // D = d_(m + 2)からd_1, ..., d_mが張る面へ直交するベクトルの大きさ
            d.push_back(parents[param::m + 1].gene - p);
            // double D = dot(d[param::m + 1], n) / norm(n);
            double D = dot(d[param::m + 1], n) / norm(n);
            D = std::fabs(D);

            // e_1, ..., e(n - m)をd_1, ..., d_(m)に直行する部分空間の正規直交基底とする
            std::vector<std::vector<double> > e;
            std::vector<std::vector<double> > plane(d);
            gram_schimidt(plane);
            std::normal_distribution<> dist(0.0, 1.0);
            while(e.size() != param::n - param::m){
                std::vector<double> norm_vec(param::n);
                for(int i = 0; i < param::n; i++) norm_vec[i] = dist(param::mt);
                std::vector<double> sum_vec(param::n, 0);
                for(int i = 0; i < plane.size(); i++) sum_vec += dot(norm_vec, plane[i]) * plane[i];
                norm_vec = norm_vec - sum_vec;
                norm_vec /= norm(norm_vec);
                plane.push_back(norm_vec);
                e.push_back(norm_vec);
            }

            // 個々体x_cを生成する
            std::vector<individual> children(param::children);
            std::normal_distribution<> w(0.0, param::sigma_xi);
            std::normal_distribution<> v(0.0, param::sigma_eta);
            for(int i = 0; i < param::children; i += 2){
                std::vector<double> wd(param::n, 0), vDe(param::n, 0);
                for(int i = 0; i < param::m; i++) wd += w(param::mt) * d[i];
                for(int i = 0; i < param::n - param::m; i++) vDe += v(param::mt) * D * e[i];
                children[i].gene = p + wd + vDe;
                children[i + 1].gene = p - wd - vDe;
                children[i].evaluate();
                children[i + 1].evaluate();
            }

            // JGGによる更新
            std::sort(children.begin(), children.end());
            for(int i = 0; i < param::m + 2; i++) population[parent_index[i]] = children[i];

            // // MGGによる更新
            // for(int i = 0; i < param::m + 2; i++) children.push_back(parents[i]);
            // std::vector<int> change_index;
            // individual best_indiv = best_select(children, change_index);
            // individual roulette_indiv = best_select(children, change_index);
            // if(std::find(parents.begin(), parents.end(), children[change_index[0]]) == parents.end()) population[parent_index[0]] = best_indiv;
            // if(std::find(parents.begin(), parents.end(), children[change_index[1]]) == parents.end()) population[parent_index[1]] = roulette_indiv;

            // 最も良い評価値の出力
            std::cout << "generation : " << g << ", fitness = " << std::min_element(population.begin(), population.end())->fitness << std::endl;
            if(std::min_element(population.begin(), population.end())->fitness < param::opt_fitness){
                opt_count++;
                break;
            }
        }
    }

    std::cout << "opt count : " << opt_count << std::endl;

    return 0;
}