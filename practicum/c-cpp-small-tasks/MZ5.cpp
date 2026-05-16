#include <iostream>
#include <cmath>
using std::cout, std::cin, std::endl, std::ostream;


class Vec{
    double * v;
    int len;
public:
    explicit Vec(int len_inp, double *coord = nullptr);
    Vec(const Vec &a);
    ~Vec();
    void set(double arg, int coord);
    double get(int coord) const{
        if ((coord>=len)||(coord<0)) return 0;
        return v[coord];
    }
    double euc_norm() const;
    double max_norm() const;
    void print() const;
    Vec operator+(const Vec & op) const;
    Vec operator-(const Vec & op) const;
    Vec operator*(double a) const;
    bool operator==(const Vec & op) const;
    double& operator[](const int index);
    const Vec& operator=(const Vec & op);
    friend Vec operator*(double a, const Vec & op);
    friend ostream& operator<<(ostream& os, const Vec& op);
};

Vec Vec::operator+(const Vec & op) const{
    int tmp_len = len;
    Vec tmp(tmp_len);
    for (int i = 0; i < tmp_len; i++){
        tmp.v[i] = v[i] + op.v[i];
    }
    return tmp;
}
Vec Vec::operator-(const Vec & op) const{
    int tmp_len = len;
    Vec tmp(tmp_len);
    for (int i = 0; i < tmp_len; i++){
        tmp.v[i] = v[i] - op.v[i];
    }
    return tmp;
}

Vec Vec::operator*(double a) const{
    int tmp_len = len;
    Vec tmp(tmp_len);
    for (int i = 0; i < tmp_len; i++){
        tmp.v[i] = v[i] * a;
    }
    return tmp;
}

Vec operator*(double a, const Vec& op){
    int tmp_len = op.len;
    Vec tmp(tmp_len);
    for (int i = 0; i < tmp_len; i++){
        tmp.v[i] = op.v[i] * a;
    }
    return tmp;
}

const Vec& Vec::operator=(const Vec & op){
    if (op == *this) return *this;
    delete []v;
    len = op.len;
    v = new double[len];
    for (int i = 0; i < len; i++){
        v[i] = op.v[i];
    }
    return *this;
}

bool Vec::operator==(const Vec & op) const{
    if (op.len != len) return false;
    for (int i = 0; i < len; i++){
        if (v[i] != op.v[i]) return false;
    }
    return true;
}

double & Vec::operator[](const int index){
    return v[index];
}


Vec::Vec(int len_inp, double *coord){
    len = len_inp;
    v = new double[len];
    if (coord == nullptr) for (int i = 0; i < len; i++) v[i] = 0; else
        for (int i = 0; i < len; i++) v[i] = coord[i];
}

Vec::Vec(const Vec &p){
    len = p.len;
    v = new double[len];
    for (int i = 0; i < len; i++){
        v[i] = p.v[i];
    }
}
Vec::~Vec(){
    delete []v;
}

ostream& operator<<(ostream& os, const Vec& op){
    os << '(';
    for (int i = 0; i < op.len - 1; i++){
        os << op.v[i];
        os << ',';
    }
    os << op.v[op.len - 1];
    os << ')';
    return os;
}


void Vec::set(double arg, int coord){
    if ((coord >= len)||(coord < 0)) return;
    v[coord] = arg;
}

double Vec::euc_norm() const{
    double res = 0;
    for (int i = 0; i < len; i++) res += v[i]*v[i];
    return sqrt(res);
}

double Vec::max_norm() const{
    double max = -1;
    for (int i=0; i<len; i++){
        if (abs (v[i]) > max) max = abs( v[i]);
    }
    return max;
}
void Vec::print() const{
    cout << "(";
    for (int i = 0; i < len - 1; i++){
        cout << v[i] << ",";
    }
    cout << v[len-1] << ')';
}

int main(){
    return 0;
}

