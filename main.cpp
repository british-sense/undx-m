#include <iostream>
#include <vector>
#include <random>

#include "parameter.hpp"
#include "individual.hpp"
#include "operation.hpp"

int main(){

    for(int t = 1; t <= param::trial; t++){

        // 母集団の生成
        std::vector<individual> population(param::population);

        for(int g = 1; g <= param::generation; g++){

            // m + 1個の親子体x_i(i = 1, ..., m + 1)をランダムに選択する
            std::vector<individual> parents(param::m + 1);
            for(int i = 0; i < param::m + 1; i++) parents[i].select(population);

            // 親子体の重心pを求める
            std::vector<double> p(param::n, 0);
            for(int i = 0; i < param::m + 1; i++) p += parents[i].gene; p /= (param::m + 1);

            // pと各個体x_iの差分ベクトルd_i = x_i - pを求める
            std::vector<double> d(param::n);
            for(int i = 0; i < param::m + 1; i++) d = parents[i].gene - p;

            // m + 2番目の親子体x_(m + 2)をランダムに選択する
            individual p_m2;
            p_m2.select(population);

            // D = d_(m + 2)からd_1, ..., d_mが生成する面へ直交するベクトルの大きさ
            double D = 0.;

            // e_1, ..., e(n - m)をd_1, ..., d_(m)に直行する部分空間の正規直交基底とする
            std::vector<std::vector<double> > e(param::n - param::m, std::vector<double>(param::n));

            // 個々体x_cを生成する
            std::vector<individual> children(param::children);
            std::normal_distribution<> dist_xi(0.0, param::sigma_xi);
            std::normal_distribution<> dist_eta(0.0, param::sigma_eta);
            for(int i = 0; i < param::children; i++){
                std::vector<double> wd(param::n, 0), vDe(param::n, 0);
                for(int i = 0; i < param::m; i++) wd += dist_xi(param::mt) * d[i];
                for(int i = 0; i < param::n - param::m; i++) vDe += dist_eta(param::mt) * D * e[i];
                children[i].gene = p + wd + vDe;
            }

        }
    }

    return 0;
}