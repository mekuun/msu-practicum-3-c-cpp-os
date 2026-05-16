#include<iostream>
#include<cstdio>
using std::cout; using std::endl;

int count_symbols(int numb){
    int i = 1;
    while ((abs(numb) / 10) > 0){
        numb /= 10;
        i += 1;
    }
    return i;
}

int count_symbols(int* arr, int n){
    int m = 0;
    for(int i = 0; i < n; i ++){
        m += count_symbols(arr[i]);
    }
    return m;
}

int count_symbols(int* ptr){
    return count_symbols(*ptr);
}

int count_symbols(const char*str){
    return strlen(str);
}

int count_symbols(double f, int n) {
    return count_symbols((int)f) + n;
}

int count_symbols(double f) {
    return count_symbols((int)f);
}
