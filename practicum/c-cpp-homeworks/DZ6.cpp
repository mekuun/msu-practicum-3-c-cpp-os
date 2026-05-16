#include <iostream>
enum {INCR = 2};
using std::cout, std::endl;
template<class T>
class Set{
    T *set;
    int allocated, used;
public:
    Set():allocated(0), used(0){};
    Set(T *arr, int len);
    Set(Set<T> const &other);
    void add(T elem);
    void add(T *arr, int len);
    void del(T elem);
    bool in(T elem) const;
    void print() const;
    Set<T> operator+(const Set<T> &other) const;
    Set<T> operator*(const Set<T> &other) const;
};

template<class T>
Set<T>::Set(T *arr, int len){
    allocated = 0;
    used = 0;
    add(arr, len);
}

template<class T> Set<T>::Set(const Set<T> &op){
    if(op.used == 0) return;
    set = new T[op.allocated];
    used = op.used;
    allocated = op.allocated;
    for(int i = 0; i < allocated; i++) set[i] = op.set[i];
}


template<class T>
bool Set<T>::in(const T elem) const {
    for(int i = 0; i < used; i++)
        if (set[i] == elem) return true;
    return false;
}

template<class T>
void Set<T>::add(const T element){
    if(used == allocated){
        allocated += sizeof(int) * INCR;
        T *set_tmp= new T[allocated];
        for(int i = 0; i < used; i++) set_tmp[i] = set[i];
        if(used != 0) delete[] set;
        set = set_tmp;
    }
    if (!in(element)){
        set[used]=element;
        used +=1;
    }
    return;
}

template<class T>
void Set<T>::add(T *arr, int len){
    if(len == 0) return;
    for(int i = 0; i < len; i++){
        add(arr[i]);
    }

}

template<class T>
void Set<T>::del(const T elem){
    for(int i = 0; i < used; i++)
        if(set[i] == elem){
            for(int j = i + 1; j < used; j++){
                set[j - 1] = set[j];
            }
            used--;
            break;
        }
}

template<class T> void Set<T>::print()const{
    if(used == 0){
        cout << endl;
        return;
    }
    Set<T> tmp = *this;
    bool flag;
    for (int i = 0; i < tmp.used - 1; i++){
        flag = false;
        for (int j = 0; j < tmp.used - i - 1; j++) {
            if (tmp.set[j] > tmp.set[j + 1]){
                T temp = tmp.set[j];
                tmp.set[j] = tmp.set[j + 1];
                tmp.set[j + 1] = temp;
                flag = true;
            }
        }
        if (!flag)
            break;
    }
    for(int i = 0; i < tmp.used-1; i++) cout << tmp.set[i] << ' ';
    cout << tmp.set[tmp.used - 1] << endl;
}

template<class T> Set<T> Set<T>::operator+(const Set<T> &op) const {
    Set<T> union_set;
    union_set.add(set, used);
    union_set.add(op.set, op.used);
    return union_set;
}
template<class T> Set<T> Set<T>::operator*(const Set<T> &op) const {
    Set<T> intersect_set;
    for(int i = 0; i < used; i++)
        if(op.in(set[i])) intersect_set.add(set[i]);
    return intersect_set;
}


/* int main()
{
    int a[] = { 1,2,3,4,5 };
    int b[] = { 3,2,6};
    Set <int> seti1(a,5),seti2,seti3,seti4;
    seti2.add(b, 3);
    seti1.print();
    seti2.print();
    seti3 = seti1*seti2;
    cout << "Intersect: ";
    seti3.print();
    seti4 = seti1 + seti2;
    cout << "Union: ";
    seti4.print();
    seti3.add(7);
    seti4.del(3);
    seti3.print();
    seti4.print();
    return 0;
} */