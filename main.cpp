#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

#include "parameter.hpp"
#include "utils.hpp"
#include "individual.hpp"
#include "vector.hpp"

int main(){ 

    for(int t = 1; t <= param::trial; t++){

        param::mt = std::mt19937(t);

        // 母集団の生成
        std::vector<individual> population(param::population);

        for(int g = 1; g <= param::generation; g++){

            // m + 1個の親子体x_i(i = 1, ..., m + 1)をランダムに選択する
            std::vector<int> parent_index(param::m + 2);
            std::vector<individual> parents(param::m + 2);
            for(int i = 0; i < param::m + 1; i++) parent_index[i] = random_select(parents[i], population);

            // 親子体の重心pを求める
            std::vector<double> p(param::n, 0);
            for(int i = 0; i < param::m + 1; i++) p += parents[i].gene;
            p /= (param::m + 1);

            // pと各個体x_iの差分ベクトルd_i = x_i - pを求める
            std::vector<std::vector<double> > d(param::m + 2, std::vector<double>(param::n));
            for(int i = 0; i < param::m + 1; i++) d[i] = parents[i].gene - p;

            // m + 2番目の親子体x_(m + 2)をランダムに選択する
            parent_index[param::m + 1] = random_select(parents[param::m + 1], population);

            // d_1, ..., d_mが張る面の法線nを求める
            std::vector<std::vector<double> > plane(d.begin(), d.begin() + param::m);
            std::vector<double> n(param::n);
            n = normal(plane);

            // D = d_(m + 2)からd_1, ..., d_mが張る面へ直交するベクトルの大きさ
            d[param::m + 1] = parents[param::m + 1].gene - p;
            // double D = dot(d[param::m + 1], n) / norm(n);
            double D = dot(d[param::m + 1], n) / norm(n);
            D = std::fabs(D);

            // e_1, ..., e(n - m)をd_1, ..., d_(m)に直行する部分空間の正規直交基底とする
            std::vector<std::vector<double> > e(param::n + 1, std::vector<double>(param::n));
            std::normal_distribution<> dist(0.0, 1.0);
            for(int i = 0; i < param::n + 1; i++){
                if(i < param::m + 1) e[i] = d[i];
                else{
                    for(int j = 0; j < param::n + 1; j++){
                        e[i][j] = dist(param::mt);
                    }
                }
            }
            gram_schimidt(e);

            // 個々体x_cを生成する
            std::vector<individual> children(param::children);
            std::normal_distribution<> w(0.0, param::sigma_xi);
            std::normal_distribution<> v(0.0, param::sigma_eta);
            for(int i = 0; i < param::children; i += 2){
                std::vector<double> wd(param::n, 0), vDe(param::n, 0);
                for(int i = 0; i < param::m; i++) wd += w(param::mt) * d[i];
                for(int i = e.size() - 1; i >= e.size() - 1 - param::n + param::m; i--) vDe += v(param::mt) * D * e[i];
                children[i].gene = p + wd + vDe;
                children[i + 1].gene = p - wd - vDe;
                children[i].evaluate();
                children[i + 1].evaluate();
            }

            // 親個体中のランダムな２個体を変更する
            for(int i = 0; i < param::m + 2; i++) children.push_back(parents[i]);
            std::uniform_int_distribution<> select_parent(0, param::m);
            int best_index = select_parent(param::mt);
            int roulette_index = select_parent(param::mt);
            best_index = best_select(population[parent_index[best_index]], children);
            roulette_index = roulette_select(population[parent_index[roulette_index]], children);

            // 最も良い評価値の出力
            std::cout << "generation : " << g << ", fitness = " << std::min_element(population.begin(), population.end())->fitness << std::endl;
        }
    }

    return 0;
}