#include <iostream>
#include <vector>
#include <cstring>
using std::cout, std::cin, std::cerr, std::endl, std::ostream, std::istream, std::string,std::vector;
enum commands{IRB, IRA, ICB, ICA, DR, DC, SR, SC, T, ERR, b, a};


class Matrix {
private:
    vector<int> matrix;
    int n, m;
public:
    Matrix(int n_, int m_);
    void print() const;
    void insert(int num, int mode);
    void delet(int num);
    void swap(int num1, int num2);
    void trans();
};

void Matrix::trans() {
    if (matrix.empty()) return;
    vector<int> tmp(n * m, 0);
    auto it1 = matrix.begin();
    auto it2 = tmp.begin();
    int tmpn = m, tmpm = n;

    for (int k = 0; k < n; k ++){
        it2 = tmp.begin() + k;
        for (int j = 0; j < m; j++){
            *it2 = *it1;
            it1++;
            it2 += tmpm;
        }
    }

    matrix = tmp;
    n = tmpn;
    m = tmpm;
}

void Matrix::swap(int num1, int num2){
    if (matrix.empty()) return;
    if (num1 < 1 || num1 > n || num2 < 1 || num2 > n || num1 == num2) return;
    auto it1 = matrix.begin(); it1 += (num1 - 1) * m;
    auto it2 = matrix.begin(); it2 += (num2 - 1) * m;

    for (int k = 0; k < m; k ++){
        int tmp = *it1;
        *it1 = *it2;
        *it2 = tmp;
        it1++;it2++;
    }
};

void Matrix::delet(int num) {
    if (matrix.empty()) return;
    if (num < 1 || num > n) return;
    auto it = matrix.begin();
    it += (num - 1) * m;
    for (int k = 0; k < m; k ++){
        matrix.erase(it);
    }
    n --;
}

void Matrix::insert(int num, int mode) {
    if (mode == b && (num < 1 || num > n )) return;
    if (mode == a && (num < 1 || num > n + 1 )) return;

    vector<int> newRow(m);
    for (int &val : newRow) cin >> val;

    auto it = matrix.begin() + (num - 1) * m;
    matrix.insert(it, newRow.begin(), newRow.end());
    n ++;
}

void Matrix::print() const {
    int counter = 1;
    for (auto i = matrix.begin(); i != matrix.end(); i++) {
        if (counter % m != 0) {
            cout << *i << ' ';
            counter++;
        }
        else {
            counter = 1;
            cout << *i << endl;
        }
    }
}

Matrix::Matrix(int n_, int m_) : n(n_), m(m_) {
    int cur;
    int len = m_ * n_;
    for (int i = 0; i < len; i++) {
        cin >> cur;
        matrix.push_back(cur);
    }
}

int parse(int argc, char **argv){
    if(argc==2 && !strcmp(argv[1], "-t")) return T;
    if(argc==3){
        if(!strcmp(argv[1], "-irb")) return IRB;
        else if(!strcmp(argv[1], "-ira")) return IRA;
        else if(!strcmp(argv[1], "-icb")) return ICB;
        else if(!strcmp(argv[1], "-ica")) return ICA;
        else if(!strcmp(argv[1], "-dr")) return DR;
        else if(!strcmp(argv[1], "-dc")) return DC;
        return ERR;
    }
    if(argc==4){
        if(!strcmp(argv[1], "-sr")) return SR;
        else if(!strcmp(argv[1], "-sc")) return SC;
        return ERR;
    }
    return ERR;
}

int main(int argc, char ** argv){
    int n, m;
    cin >> n >> m;
    Matrix mat(n,m);
    int mode = parse(argc, argv);
    switch (mode){
        case T: {mat.trans(); break;}
        case IRB: {mat.insert(atoi(argv[2]), b); break;}
        case IRA: {mat.insert(atoi(argv[2]) + 1, a); break;}
        case ICB: {mat.trans(); mat.insert(atoi(argv[2]), b); mat.trans(); break;}
        case ICA: {mat.trans(); mat.insert(atoi(argv[2]) + 1, a); mat.trans(); break;}
        case DR: {mat.delet(atoi(argv[2])); break;}
        case DC: {mat.trans(); mat.delet(atoi(argv[2])); mat.trans(); break;}
        case SR: {mat.swap(atoi(argv[2]), atoi(argv[3])); break;}
        case SC: {mat.trans(); mat.swap(atoi(argv[2]), atoi(argv[3])); mat.trans(); break;}
        default: break;
    }
    mat.print();
}

// 4 5 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20