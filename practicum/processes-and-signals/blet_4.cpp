#include <iostream>
#include <cmath>
using std::cout, std::cin, std::cerr, std::endl, std::ostream;
enum {INTERVAL_ERR = 0, INTERCECTION_ERR = 1, UNION_ERR = 2};

class Interval_except{
private:
    int errcode;
public:
    Interval_except(int errcode_inp):errcode(errcode_inp){};
    void print();
};

void Interval_except::print() {
    switch (errcode) {
        case INTERVAL_ERR:
            cerr << "Exception: Incorrect interval" << endl;
            break;
        case INTERCECTION_ERR:
            cerr << "Exception: Incorrect intersection" << endl;
            break;
        case UNION_ERR:
            cerr << "Exception: Incorrect union" << endl;
            break;
        default:
            cerr << "Exception: unknown error" << endl;
            break;
    }
}

template<typename T>
class Interval{
private:
    T left, right;
public:
    explicit Interval(T l, T r);
    void print() const;
    Interval<T> intersection(const Interval<T> & other);
    Interval<T> unionsection(const Interval<T> & other);
};

template<typename T>
Interval<T> Interval<T>:: intersection(const Interval<T> & other){
    Interval<T> tmp(0, 0);
    other.left > left? tmp.left = other.left: tmp.left = left;
    other.right < right? tmp.right = other.right: tmp.right = right;
    if (tmp.right < tmp.left)  throw Interval_except(INTERCECTION_ERR);
    return tmp;
}

template<typename T>
Interval<T> Interval<T>:: unionsection(const Interval<T> & other){
    Interval<T> tmp(0, 0);
    if ((other.left > right) || (left > other.right)) throw Interval_except(UNION_ERR);
    other.left < left? tmp.left = other.left: tmp.left = left;
    other.right > right? tmp.right = other.right: tmp.right = right;
    return tmp;
}

template<typename T>
Interval<T>::Interval(T l, T r){
    if (r < l) throw Interval_except(INTERVAL_ERR);
    right = r;
    left = l;
}

template<typename T>
void Interval<T>::print() const{
    cout << "(" << left << " , " << right << ")" << endl;
}

int main(){
    try {
        Interval<int> blyatblyatblyatblyat(4,10), aaaaaaaaaaaaaaaa(0, 3);
        Interval<int> AAAAHAHAHAHAHAAHAA = blyatblyatblyatblyat.intersection(aaaaaaaaaaaaaaaa), hmm = blyatblyatblyatblyat.unionsection(aaaaaaaaaaaaaaaa);
        blyatblyatblyatblyat.print(), aaaaaaaaaaaaaaaa.print(), AAAAHAHAHAHAHAAHAA.print(), hmm.print();
    }
    catch(Interval_except &hahahihi) {
        hahahihi.print();
    }
    catch(Interval_except &lalala) {
        lalala.print();
    }
    return 0;
}