#include <iostream>
#include <cmath>
using std::cout, std::cin, std::cerr, std::endl, std::ostream;
enum {LEN_ERR = 1, COORD_GET_ERR = 2, COORD_SET_ERR = 3, ADD_ERR = 4, INDEX_ERR = 5, MULT_ERR = 6};
template<typename T>
class Vec{
    T* v;
    int len;
public:
    explicit Vec(int len_inp, T *coord = nullptr);
    Vec(const Vec &a);
    ~Vec();
    void set(T arg, int coord);
    T get(int coord) const;
    T max_norm() const;
    void print() const;
    Vec<T> operator+(const Vec<T> & op) const;
    const Vec<T>& operator+=(const Vec &other);
    Vec<T> operator-(const Vec<T> & op) const;
    Vec<T> operator*(T a) const;
    T operator^(const Vec<T> & op) const;
    bool operator==(const Vec<T> & op) const;
    T& operator[](int index);
    const Vec<T>& operator=(const Vec<T> & op);

    template<typename V>
    friend Vec<V> operator*(V a, const Vec<V> & op);
    template<typename I>
    friend ostream& operator<<(ostream& os, const Vec<I>& op);
};


class except {
    int errcode, indx, l1, l2;
public:
    except() {
        errcode = 0;
    }
    except(int i) {
        errcode = i;
    }
    except(int i, int l1_inp, int l2_inp) {
        errcode = i;
        l1 = l1_inp;
        l2 = l2_inp;
    }
    except(int i, int inp_indx) {
        indx = inp_indx;
        errcode = i;
    }

    void print() const{
        switch(errcode) {
            case LEN_ERR:
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
            case MULT_ERR:
                cerr <<  "Exception: multiplication of vectors of different lengths: " << l1 << " " << l2 << endl;
                break;
            default:
                cerr << "Exception: unknown error" << endl;
        }
    }
};


template<class T>const Vec<T>& Vec<T>::operator+=(const Vec<T> &other){
    if (len!=other.len) throw(except(ADD_ERR, len, other.len));
    for (int i=0; i<len; i++) v[i]+=other.v[i];
    return *this;
}


template<typename T>
T Vec<T>:: operator^(const Vec<T> & op) const{
    if (len != op.len) {throw except(MULT_ERR, len, op.len);}
    T sum = 0;
    for (int i = 0; i < len; i++){
        sum += op.v[i] * v[i];
    }
    return sum;
}

template<typename T>
Vec<T> Vec<T>::operator+(const Vec<T> & op) const{
    if (len != op.len) {throw except(ADD_ERR, len, op.len);}
    int tmp_len = len;
    Vec tmp(tmp_len);
    for (int i = 0; i < tmp_len; i++){
        tmp.v[i] = v[i] + op.v[i];
    }
    return tmp;
}

template<typename T>
Vec<T> Vec<T>::operator-(const Vec<T> & op) const{
    if (len != op.len) {throw except(0);}
    int tmp_len = len;
    Vec tmp(tmp_len);
    for (int i = 0; i < tmp_len; i++){
        tmp.v[i] = v[i] - op.v[i];
    }
    return tmp;
}

template<typename T>
Vec<T> Vec<T>::operator*(T a) const{
    int tmp_len = len;
    Vec tmp(tmp_len);
    for (int i = 0; i < tmp_len; i++){
        tmp.v[i] = v[i] * a;
    }
    return tmp;
}

template<typename V>
Vec<V> operator*(V a, const Vec<V>& op){
    int tmp_len = op.len;
    Vec<V> tmp(tmp_len);
    for (int i = 0; i < tmp_len; i++){
        tmp.v[i] = op.v[i] * a;
    }
    return tmp;
}

template<typename T>
const Vec<T>& Vec<T>::operator=(const Vec<T> & op){
    if (op == *this) return *this;
    delete []v;
    len = op.len;
    v = new T[len];
    for (int i = 0; i < len; i++){
        v[i] = op.v[i];
    }
    return *this;
}

template<typename T>
bool Vec<T>::operator==(const Vec<T> & op) const{
    if (op.len != len) return false;
    for (int i = 0; i < len; i++){
        if (v[i] != op.v[i]) return false;
    }
    return true;
}

template<typename T>
T & Vec<T>::operator[](const int index){
    if (index < 0 || index >= len) {throw except(INDEX_ERR, index);}
    return v[index];
}


template<typename T>
Vec<T>::Vec(int len_inp, T *coord){
    if (len_inp < 0) {throw except(LEN_ERR);}
    len = len_inp;
    v = new T[len];
    if (coord == nullptr) for (int i = 0; i < len; i++) v[i] = 0; else
        for (int i = 0; i < len; i++) v[i] = coord[i];
}

template<typename T>
Vec<T>::Vec(const Vec &p){
    len = p.len;
    v = new T[len];
    for (int i = 0; i < len; i++){
        v[i] = p.v[i];
    }
}

template<typename T>
Vec<T>::~Vec(){
    delete []v;
}

template<typename I>
ostream& operator<<(ostream& os, const Vec<I>& op){
    os << '(';
    for (int i = 0; i < op.len - 1; i++){
        os << op.v[i];
        os << ',';
    }
    os << op.v[op.len - 1];
    os << ')';
    return os;
}

template<typename T>
T Vec<T>::get(int coord) const{
    if ((coord >= len)||(coord < 0)) throw except(COORD_GET_ERR);
    return v[coord];
}

template<typename T>
void Vec<T>::set(T arg, int coord){
    if ((coord >= len)||(coord < 0)) throw except(COORD_SET_ERR);
    v[coord] = arg;
}


template<typename T>
T Vec<T>::max_norm() const{
    double max = -1;
    for (int i=0; i<len; i++){
        if (abs (v[i]) > max) max = abs( v[i]);
    }
    return max;
}

template<typename T>
void Vec<T>::print() const{
    cout << "(";
    for (int i = 0; i < len - 1; i++){
        cout << v[i] << ",";
    }
    cout << v[len-1] << ')';
}


/*void error()
{
    double y1[3] = {1,2,3};
    double y2[5] = {2,1,0,5,7};
    Vec x(-3, y1), y(5, y2), z(4);
    Vec u = x;
    y.print();
    x.print();
    z.print();
    u.print();
}*/

int main(){
    try{
        Vector();
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