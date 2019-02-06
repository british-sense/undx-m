#ifndef operation_hpp
#define operation_hpp

std::vector<double> operator+(const std::vector<double> &vec1, const double &value){
    int size = vec1.size();
    std::vector<double> vec(size, 0.);
    for(int i = 0; i < size; i++) vec[i] = vec1[i] + value;
    return vec;
}

std::vector<double> operator+(const double &value, const std::vector<double> &vec1){
    int size = vec1.size();
    std::vector<double> vec(size, 0.);
    for(int i = 0; i < size; i++) vec[i] = value + vec1[i];
    return vec;
}

std::vector<double> operator+(const std::vector<double> &vec1, const std::vector<double> &vec2){
    int size = vec1.size();
    std::vector<double> vec(size, 0.);
    for(int i = 0; i < size; i++) vec[i] = vec1[i] + vec2[i];
    return vec;
}

std::vector<double> operator-(const std::vector<double> &vec1, const double &value){
    int size = vec1.size();
    std::vector<double> vec(size, 0.);
    for(int i = 0; i < size; i++) vec[i] = vec1[i] - value;
    return vec;
}

std::vector<double> operator-(const double &value, const std::vector<double> &vec1){
    int size = vec1.size();
    std::vector<double> vec(size, 0.);
    for(int i = 0; i < size; i++) vec[i] = value - vec1[i];
    return vec;
}

std::vector<double> operator-(const std::vector<double> &vec1, const std::vector<double> &vec2){
    int size = vec1.size();
    std::vector<double> vec(size, 0.);
    for(int i = 0; i < size; i++) vec[i] = vec1[i] - vec2[i];
    return vec;
}

std::vector<double> operator*(const double &value, const std::vector<double> &vec1){
    int size = vec1.size();
    std::vector<double> vec(size, 0.);
    for(int i = 0; i < size; i++) vec[i] = value * vec1[i];
    return vec;
}

std::vector<double> operator*(const std::vector<double> &vec1, const double &value){
    int size = vec1.size();
    std::vector<double> vec(size, 0.);
    for(int i = 0; i < size; i++) vec[i] = vec1[i] * value;
    return vec;
}

std::vector<double> operator/(const std::vector<double> &vec1, const double &value){
    int size = vec1.size();
    std::vector<double> vec(size, 0.);
    for(int i = 0; i < size; i++) vec[i] = vec1[i] / value;
    return vec;
}

std::vector<double> operator/(const double &value, const std::vector<double> &vec1){
    int size = vec1.size();
    std::vector<double> vec(size, 0.);
    for(int i = 0; i < size; i++) vec[i] = value / vec1[i];
    return vec;
}

void operator+=(std::vector<double> &vec1, const std::vector<double> &vec2){
    for(int i = 0; i < vec1.size(); i++) vec1[i] += vec2[i];
}

void operator+=(std::vector<double> &vec1, const double &value){
    for(int i = 0; i < vec1.size(); i++) vec1[i] += value;
}

void operator-=(std::vector<double> &vec1, const std::vector<double> &vec2){
    for(int i = 0; i < vec1.size(); i++) vec1[i] -= vec2[i];
}

void operator-=(std::vector<double> &vec1, const double &value){
    for(int i = 0; i < vec1.size(); i++) vec1[i] -= value;
}

void operator*=(std::vector<double> &vec1, const double &value){
    for(int i = 0; i < vec1.size(); i++) vec1[i] *= value;
}

void operator/=(std::vector<double> &vec1, const double &value){
    for(int i = 0; i < vec1.size(); i++) vec1[i] /= value;
}

#endif