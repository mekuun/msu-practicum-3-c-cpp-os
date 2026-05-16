#include <iostream>
#include <cmath>
using std::cout, std::cin, std::cerr, std::endl, std::ostream;
enum {LENGTH_ERR = 1, COORD_GET_ERR = 2, COORD_SET_ERR = 3, ADD_ERR = 4, INDEX_ERR = 5};

class Vec{
    double * v;
    int len;
public:
    explicit Vec(int len_inp, double *coord = nullptr);
    Vec(const Vec &a);
    ~Vec();
    void set(double arg, int coord);
    double get(int coord) const;
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


class except {
    int errcode, indx, l1, l2;
public:
    except() {errcode = 0;}

    except(int i) {errcode = i;}

    except(int i, int l1_inp, int l2_inp);

    except(int i, int inp_indx);

    void print() const;
};

except::except(int i, int l1_inp, int l2_inp) {
    errcode = i;
    l1 = l1_inp;
    l2 = l2_inp;
}

except::except(int i, int inp_indx) {
    indx = inp_indx;
    errcode = i;
}

void except::print() const {
    switch (errcode) {
        case LENGTH_ERR:
            cerr << "Exception: length error" << endl;
            break;
        case COORD_GET_ERR:
            cerr << "Exception: coordinate error in get()" << endl;
            break;
        case COORD_SET_ERR:
            cerr << "Exception: coordinate error in set()" << endl;
            break;
        case ADD_ERR:
            cerr << "Exception: addition of vectors of different lengths: " << l1 << " " << l2 << endl;
            break;
        case INDEX_ERR:
            cerr << "Exception: incorrect indexing: " << indx << endl;
            break;
        default:
            cerr << "Exception: unknown error" << endl;
    }
}

Vec Vec::operator+(const Vec & op) const{
    if (len != op.len) {throw except(4, len, op.len);}
    int tmp_len = len;
    Vec tmp(tmp_len);
    for (int i = 0; i < tmp_len; i++){
        tmp.v[i] = v[i] + op.v[i];
    }
    return tmp;
}
Vec Vec::operator-(const Vec & op) const{
    if (len != op.len) {throw except(0);}
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
    if (index < 0 || index >= len) {throw except(5, index);}
    return v[index];
}


Vec::Vec(int len_inp, double *coord){
    if (len_inp < 0) {throw except(1);}
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

double Vec::get(int coord) const{
    if ((coord >= len)||(coord < 0)) throw except(2);
    return v[coord];
}

void Vec::set(double arg, int coord){
    if ((coord >= len)||(coord < 0)) throw except(3);
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


void error()
{
    double y1[3] = {1,2,3};
    double y2[5] = {2,1,0,5,7};
    Vec x(-3, y1), y(5, y2), z(4);
    Vec u = x;
    y.print();
    x.print();
    z.print();
    u.print();
}


int main(){
    try{
        error();
    }
    catch(except &e) {
        e.print();
    }
    catch(...) {
        except e(-1);
        e.print();
    }
    return 0;
}