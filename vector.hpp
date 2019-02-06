#ifndef vecetor_hpp
#define vecetor_hpp

#include <vector>
#include <iostream>

std::vector<double> operator+(const std::vector<double> &vec1, const double &value){
    size_t size = vec1.size();
    std::vector<double> vec(size, 0.);
    for(size_t i = 0; i < size; i++) vec[i] = vec1[i] + value;
    return vec;
}

std::vector<double> operator+(const double &value, const std::vector<double> &vec1){
    size_t size = vec1.size();
    std::vector<double> vec(size, 0.);
    for(size_t i = 0; i < size; i++) vec[i] = value + vec1[i];
    return vec;
}

std::vector<double> operator+(const std::vector<double> &vec1, const std::vector<double> &vec2){
    size_t size = vec1.size();
    std::vector<double> vec(size, 0.);
    for(size_t i = 0; i < size; i++) vec[i] = vec1[i] + vec2[i];
    return vec;
}

std::vector<double> operator-(const std::vector<double> &vec1, const double &value){
    size_t size = vec1.size();
    std::vector<double> vec(size, 0.);
    for(size_t i = 0; i < size; i++) vec[i] = vec1[i] - value;
    return vec;
}

std::vector<double> operator-(const double &value, const std::vector<double> &vec1){
    size_t size = vec1.size();
    std::vector<double> vec(size, 0.);
    for(size_t i = 0; i < size; i++) vec[i] = value - vec1[i];
    return vec;
}

std::vector<double> operator-(const std::vector<double> &vec1, const std::vector<double> &vec2){
    size_t size = vec1.size();
    std::vector<double> vec(size, 0.);
    for(size_t i = 0; i < size; i++) vec[i] = vec1[i] - vec2[i];
    return vec;
}

std::vector<double> operator*(const double &value, const std::vector<double> &vec1){
    size_t size = vec1.size();
    std::vector<double> vec(size, 0.);
    for(size_t i = 0; i < size; i++) vec[i] = value * vec1[i];
    return vec;
}

std::vector<double> operator*(const std::vector<double> &vec1, const double &value){
    size_t size = vec1.size();
    std::vector<double> vec(size, 0.);
    for(size_t i = 0; i < size; i++) vec[i] = vec1[i] * value;
    return vec;
}

std::vector<double> operator/(const std::vector<double> &vec1, const double &value){
    size_t size = vec1.size();
    std::vector<double> vec(size, 0.);
    for(size_t i = 0; i < size; i++) vec[i] = vec1[i] / value;
    return vec;
}

std::vector<double> operator/(const double &value, const std::vector<double> &vec1){
    size_t size = vec1.size();
    std::vector<double> vec(size, 0.);
    for(size_t i = 0; i < size; i++) vec[i] = value / vec1[i];
    return vec;
}

void operator+=(std::vector<double> &vec1, const std::vector<double> &vec2){
    for(size_t i = 0; i < vec1.size(); i++) vec1[i] += vec2[i];
}

void operator+=(std::vector<double> &vec1, const double &value){
    for(size_t i = 0; i < vec1.size(); i++) vec1[i] += value;
}

void operator-=(std::vector<double> &vec1, const std::vector<double> &vec2){
    for(size_t i = 0; i < vec1.size(); i++) vec1[i] -= vec2[i];
}

void operator-=(std::vector<double> &vec1, const double &value){
    for(size_t i = 0; i < vec1.size(); i++) vec1[i] -= value;
}

void operator*=(std::vector<double> &vec1, const double &value){
    for(size_t i = 0; i < vec1.size(); i++) vec1[i] *= value;
}

void operator/=(std::vector<double> &vec1, const double &value){
    for(size_t i = 0; i < vec1.size(); i++) vec1[i] /= value;
}

double dot(const std::vector<double> &vec1, const std::vector<double> &vec2){
    double value = 0.;
    for(size_t i = 0; i < vec1.size(); i++) value += vec1[i] * vec2[i];
    return value; 
}

double norm(const std::vector<double> &vec, int p = 2){
    double norm = 0.;
    for(size_t i = 0; i < vec.size(); i++) norm += vec[i] * vec[i];
    return std::pow(norm, 1. / p);
}

void gram_schimidt(std::vector<std::vector<double> > &vec){

    int dim = vec.front().size();
    std::vector<std::vector<double> > norm_vec;

    for(size_t k = 0; k < vec.size(); k++){
        std::vector<double> sum_vec(dim, 0);
        for(size_t i = 0; i < k; i++){
            sum_vec += dot(vec[k], norm_vec[i]) * norm_vec[i];
        }
        vec[k] -= sum_vec;
        if(std::count(vec[k].begin(), vec[k].end(), 0) == dim){
            vec.erase(vec.begin() + k);
            k--;
            continue;
        } 
        norm_vec.push_back(vec[k] / sqrt(dot(vec[k], vec[k])));
    }
    vec = norm_vec;
}

std::vector<double> normal(std::vector<std::vector<double> > plane){
    size_t dim = plane.front().size();
    std::vector<double> n(dim);
    // グラムシュミットの直交化法で求める
    gram_schimidt(plane);
    return plane.back();
}

void output(const std::vector<double> &vec){
    for(size_t i = 0; i < vec.size(); i++) std::cout << vec[i] << " ";
    std::cout << std::endl;
}

#endif